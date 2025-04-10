/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 11:56:42 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	setup_pipes(t_pipeline *pipeline)
{
	int	pipe_index;
	int	number_of_pipes;

	number_of_pipes = pipeline->cmd_count - 1;
	if (number_of_pipes <= 0)
	{
		pipeline->pipe_fds = NULL;
		return ;
	}
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

	if (!pipeline || !pipeline->commands)
		return ;
	cmd_index = 0;
	while (cmd_index < pipeline->cmd_count)
	{
		if (cmd_index > 0 && pipeline->pipe_fds)
			pipeline->commands[cmd_index]->pipe_read = pipeline->pipe_fds[\
			(cmd_index - 1) * 2];
		if (cmd_index < pipeline->cmd_count - 1 && pipeline->pipe_fds)
			pipeline->commands[cmd_index]->pipe_write = pipeline->pipe_fds[\
			cmd_index * 2 + 1];
		cmd_index++;
	}
}

static void	close_unused_pipes(t_pipeline *pipeline, int cmd_index)
{
	int	pipe_fd;

	pipe_fd = 0;
	while (pipe_fd < (pipeline->cmd_count - 1) * 2)
	{
		if ((cmd_index > 0 && pipe_fd == (cmd_index - 1) * 2)
			|| (cmd_index < pipeline->cmd_count - 1 && pipe_fd == cmd_index * 2
				+ 1))
		{
			pipe_fd++;
			continue ;
		}
		close(pipeline->pipe_fds[pipe_fd]);
		pipe_fd++;
	}
}

static void	create_child_processes(t_pipeline *pipeline, pid_t *child_pids)
{
	int	cmd_index;

	cmd_index = -1;
	while (++cmd_index < pipeline->cmd_count)
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
			close_unused_pipes(pipeline, cmd_index);
			execute_piped_command(pipeline->commands[cmd_index], pipeline->env);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		if (cmd_index > 0)
			close(pipeline->pipe_fds[(cmd_index - 1) * 2]);
		if (cmd_index < pipeline->cmd_count - 1)
			close(pipeline->pipe_fds[cmd_index * 2 + 1]);
	}
}

void	execute_pipeline(t_pipeline *pipeline)
{
	pid_t	*child_pids;

	if (!pipeline || !pipeline->commands || !pipeline->commands[0])
	{
		update_last_value(pipeline->env, 1);
		return ;
	}
	if (pipeline->cmd_count == 1 && pipeline->commands[0]
		&& pipeline->commands[0]->args[0]
		&& is_builtin(pipeline->commands[0]->args[0]))
	{
		handle_builtin_single_command(pipeline);
		return ;
	}
	setup_pipes(pipeline);
	setup_command_pipes(pipeline);
	child_pids = ft_calloc(pipeline->cmd_count, sizeof(pid_t));
	if (!child_pids)
		print_memory_error();
	create_child_processes(pipeline, child_pids);
	wait_for_children(child_pids, pipeline->cmd_count, pipeline->env);
	return ;
}
