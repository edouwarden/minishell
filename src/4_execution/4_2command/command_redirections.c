/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_redirections(t_command *cmd)
{
	if (cmd->input_file)
	{
		ft_gc_free(cmd->input_file);
		cmd->input_file = NULL;
	}
	if (cmd->output_file)
	{
		ft_gc_free(cmd->output_file);
		cmd->output_file = NULL;
	}
	if (cmd->heredoc_delim)
	{
		ft_gc_free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
	if (cmd->input_fd != STDIN)
	{
		close(cmd->input_fd);
		cmd->input_fd = STDIN;
	}
	if (cmd->output_fd != STDOUT)
	{
		close(cmd->output_fd);
		cmd->output_fd = STDOUT;
	}
}

void	handle_pipe_redirections(t_command *cmd)
{
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
}

void	handle_file_redirections(t_command *cmd)
{
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
}

void	handle_redirections(t_command *cmd)
{
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
}

void	handle_builtin_single_command(t_pipeline *pipeline)
{
	int	saved_stdin;
	int	saved_stdout;

	if (handle_heredoc(pipeline->commands[0]) == -1
		|| handle_input_redirection(pipeline->commands[0]) == -1
		|| handle_output_redirection(pipeline->commands[0]) == -1)
	{
		cleanup_redirections(pipeline->commands[0]);
		set_last_result(pipeline->env, 1);
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
}
