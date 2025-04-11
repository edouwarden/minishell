/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:21 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipeline	*init_pipeline(int cmd_count)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->commands = ft_calloc(cmd_count + 1, sizeof(t_command *));
	if (!pipeline->commands)
	{
		ft_gc_free(pipeline);
		return (NULL);
	}
	pipeline->cmd_count = 0;
	return (pipeline);
}

static int	handle_command_args(t_pipeline *pipeline, char **current_args)
{
	pipeline->commands[pipeline->cmd_count] = create_command(current_args);
	if (!pipeline->commands[pipeline->cmd_count])
	{
		free_array(current_args);
		return (0);
	}
	pipeline->commands[pipeline->cmd_count]->args = process_redirections(\
	pipeline->commands[pipeline->cmd_count], current_args);
	if (!pipeline->commands[pipeline->cmd_count]->args)
	{
		ft_gc_free(pipeline->commands[pipeline->cmd_count]);
		pipeline->commands[pipeline->cmd_count] = NULL;
		return (0);
	}
	return (1);
}

static int	process_command(t_pipeline *pipeline, char *cmd, int *pos,
		int *start)
{
	char	**current_args;
	int		cmd_end;

	cmd_end = (*pos);
	if (cmd[cmd_end + 1] == '\0')
		cmd_end++;
	current_args = split_args(cmd, *start, cmd_end);
	if (!current_args || !*current_args)
		return (0);
	if (!handle_command_args(pipeline, current_args))
		return (0);
	pipeline->cmd_count++;
	*start = *pos + 1;
	return (1);
}

static int	process_command_line(t_pipeline *pipeline, char *cmd)
{
	int		current_pos;
	int		cmd_start;
	char	current_quote;

	current_pos = 0;
	cmd_start = 0;
	current_quote = 0;
	while (cmd[current_pos])
	{
		if ((cmd[current_pos] == '|' && !current_quote) || cmd[\
		current_pos + 1] == '\0')
		{
			if (!process_command(pipeline, cmd, &current_pos, &cmd_start))
			{
				free_pipeline(pipeline);
				return (0);
			}
		}
		handle_quotes(cmd[current_pos], &current_quote);
		current_pos++;
	}
	pipeline->commands[pipeline->cmd_count] = NULL;
	return (1);
}

t_pipeline	*split_command(char *cmd)
{
	t_pipeline	*pipeline;

	if (!cmd)
		return (NULL);
	pipeline = init_pipeline(count_commands(cmd));
	if (!pipeline)
		return (NULL);
	if (!process_command_line(pipeline, cmd))
		return (NULL);
	return (pipeline);
}
