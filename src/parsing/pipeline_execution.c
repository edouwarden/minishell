/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 11:56:42 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_pipes(t_pipeline *pipeline)
{
	int	pipe_index;
	int	number_of_pipes;

	number_of_pipes = pipeline->cmd_count - 1;
	pipeline->pipe_fds = ft_calloc(number_of_pipes * 2, sizeof(int));
	if (!pipeline->pipe_fds)
		print_memory_error();
	pipe_index = 0;
	while (pipe_index < number_of_pipes)
	{
		if (pipe(&pipeline->pipe_fds[pipe_index * 2]) == -1)
		{
			perror("pipe");
			free_pipeline(pipeline);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		pipe_index++;
	}
}

static void	setup_command_pipes(t_pipeline *pipeline)
{
	int	cmd_index;

	cmd_index = 0;
	debug_printf("pipeline, cmd_count: %d", pipeline->cmd_count);
	debug_printf("pipeline, first command, pipe read: %d", pipeline->commands[cmd_index]->pipe_read);
	debug_printf("pipeline, first command, pipe write: %d", pipeline->commands[cmd_index]->pipe_write);
	debug_printf("pipeline, first command, pipe fds in: %d", pipeline->pipe_fds[(cmd_index - 1) * 2]);
	debug_printf("pipeline, first command, pipe fds out: %d", pipeline->pipe_fds[cmd_index * 2 + 1]);
	while (cmd_index < pipeline->cmd_count)
	{
		if (cmd_index > 0)
			pipeline->commands[cmd_index]->pipe_read = pipeline->pipe_fds[(cmd_index
					- 1) * 2];
		if (cmd_index < pipeline->cmd_count - 1)
			pipeline->commands[cmd_index]->pipe_write = pipeline->pipe_fds[cmd_index
				* 2 + 1];
		cmd_index++;
	}
}

static void	execute_piped_command(t_command *cmd, t_env **envp)
{
	char	*command_path;
	char	**env;
	int		status;

	status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->heredoc_delim && handle_heredoc(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	if (handle_input_redirection(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	if (handle_output_redirection(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	if (!cmd->args[0])
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_SUCCESS);
	}
	if (cmd->pipe_read != -1)
	{
		if (dup2(cmd->pipe_read, STDIN) == -1)
		{
			perror("dup2: pipe read redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe_read);
	}
	if (cmd->pipe_write != -1)
	{
		if (dup2(cmd->pipe_write, STDOUT) == -1)
		{
			perror("dup2: pipe write redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe_write);
	}
	if (cmd->input_fd != STDIN)
	{
		if (dup2(cmd->input_fd, STDIN) == -1)
		{
			perror("dup2: input file redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->output_fd != STDOUT)
	{
		if (dup2(cmd->output_fd, STDOUT) == -1)
		{
			perror("dup2: output file redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
	}
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd->args, envp);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(status);
	}
	env = convert_env_to_array(envp);
	if (!env)
	{
		perror("Failed to create environment array");
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			if (access(cmd->args[0], X_OK) == -1)
			{
				print_permission_errors(cmd->args[0]);
				free_array(env);
				cleanup_redirections(cmd);
				ft_gc_cleanup();
				exit(126);
			}
			command_path = ft_strdup(cmd->args[0]);
		}
		else
		{
			print_command_error(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(127);
		}
	}
	else
	{
		command_path = find_command_path(cmd->args[0], env);
		if (!command_path)
		{
			print_command_error(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(127);
		}
	}
	status = execve(command_path, cmd->args, env);
	if (status == -1)
	{
		perror("execve: command execution failed");
		ft_gc_free(command_path);
		free_array(env);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(126);
	}
}

void	execute_pipeline(t_pipeline *pipeline)
{
	int		cmd_index;
	pid_t	*child_pids;
	int		status;
	int		last_command_status;
	int		saved_stdin;
	int		saved_stdout;
	int		pipe_fd;

	if (pipeline->cmd_count == 1 && is_builtin(pipeline->commands[0]->args[0]))
	{
		if (handle_heredoc(pipeline->commands[0]) == -1
			|| handle_input_redirection(pipeline->commands[0]) == -1
			|| handle_output_redirection(pipeline->commands[0]) == -1)
		{
			cleanup_redirections(pipeline->commands[0]);
			update_last_value(pipeline->env, 1);
			return ;
		}
		saved_stdin = dup(STDIN);
		saved_stdout = dup(STDOUT);
		if (pipeline->commands[0]->input_fd != STDIN)
			dup2(pipeline->commands[0]->input_fd, STDIN);
		if (pipeline->commands[0]->output_fd != STDOUT)
			dup2(pipeline->commands[0]->output_fd, STDOUT);
		execute_builtin(pipeline->commands[0]->args, pipeline->env);
		dup2(saved_stdin, STDIN);
		dup2(saved_stdout, STDOUT);
		close(saved_stdin);
		close(saved_stdout);
		cleanup_redirections(pipeline->commands[0]);
		return ;
	}
	setup_pipes(pipeline);
	setup_command_pipes(pipeline);
	child_pids = ft_calloc(pipeline->cmd_count, sizeof(pid_t));
	if (!child_pids)
		print_memory_error();
	cmd_index = 0;
	while (cmd_index < pipeline->cmd_count)
	{
		child_pids[cmd_index] = fork();
		if (child_pids[cmd_index] == -1)
		{
			perror("fork: Erreur lors de la création du processus");
			ft_gc_free(child_pids);
			update_last_value(pipeline->env, 1);
			return ;
		}
		if (child_pids[cmd_index] == 0)
		{
			pipe_fd = 0;
			while (pipe_fd < (pipeline->cmd_count - 1) * 2)
			{
				if ((cmd_index > 0 && pipe_fd == (cmd_index - 1) * 2)
					|| (cmd_index < pipeline->cmd_count - 1
						&& pipe_fd == cmd_index * 2 + 1))
				{
					pipe_fd++;
					continue ;
				}
				close(pipeline->pipe_fds[pipe_fd]);
				pipe_fd++;
			}
			execute_piped_command(pipeline->commands[cmd_index], pipeline->env);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		if (cmd_index > 0)
			close(pipeline->pipe_fds[(cmd_index - 1) * 2]);
		if (cmd_index < pipeline->cmd_count - 1)
			close(pipeline->pipe_fds[cmd_index * 2 + 1]);
		cmd_index++;
	}
	last_command_status = 0;
	cmd_index = pipeline->cmd_count - 1;
	while (cmd_index >= 0)
	{
		waitpid(child_pids[cmd_index], &status, 0);
		if (cmd_index == pipeline->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_command_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_command_status = 128 + WTERMSIG(status);
			update_last_value(pipeline->env, last_command_status);
		}
		cmd_index--;
	}
	ft_gc_free(child_pids);
	update_last_value(pipeline->env, last_command_status);
	return ;
}
