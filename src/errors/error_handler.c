/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:30:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 14:04:40 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_gc_free(arr[i]);
		i++;
	}
	ft_gc_free(arr);
}

void	ft_gc_free_commands(t_command **commands, int count)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (i < count && commands[i])
	{
		if (commands[i]->args)
			free_array(commands[i]->args);
		if (commands[i]->pipe_read != -1)
			close(commands[i]->pipe_read);
		if (commands[i]->pipe_write != -1)
			close(commands[i]->pipe_write);
		if (commands[i]->input_fd != STDIN)
			close(commands[i]->input_fd);
		if (commands[i]->output_fd != STDOUT)
			close(commands[i]->output_fd);
		ft_gc_free(commands[i]);
		i++;
	}
	ft_gc_free(commands);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->commands)
		ft_gc_free_commands(pipeline->commands, pipeline->cmd_count);
	if (pipeline->pipe_fds)
		ft_gc_free(pipeline->pipe_fds);
	ft_gc_free(pipeline);
}
