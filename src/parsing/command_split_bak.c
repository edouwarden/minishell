/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:21 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 14:12:21 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pipeline	*init_pipeline(char *cmd)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd_count = count_pipes(cmd);
	pipeline->commands = ft_calloc(pipeline->cmd_count + 1,
			sizeof(t_command *));
	if (!pipeline->commands)
		ft_gc_free(pipeline);
	return (pipeline);
}

int	handle_command_processing(char *cmd, t_pipeline *pipeline,
		int *cmd_count, int pos)
{
	char	**current_args;
	int		cmd_start;

	cmd_start = pos - (cmd[pos] == '|');
	debug_printf("start args %d end args %d", cmd_start,  pos + (cmd[pos + 1] == '\0'));
	current_args = split_args(cmd, cmd_start, pos + (cmd[pos + 1] == '\0'));
	debug_str_list(current_args);
	if (!current_args || !*current_args)
		return (0);
	pipeline->commands[*cmd_count] = create_command(current_args);
	if (!pipeline->commands[*cmd_count])
	{
		free_array(current_args);
		return (0);
	}
	pipeline->commands[*cmd_count]->args = process_redirections(\
		pipeline->commands[*cmd_count], current_args);
	return (pipeline->commands[*cmd_count]->args != NULL);
}

void	process_commands(char *cmd, t_pipeline *pipeline)
{
	int		pos;
	int		cmd_count;
	char	current_quote;

	pos = -1;
	cmd_count = 0;
	current_quote = 0;
	while (cmd[++pos])
	{
		debug_printf("test %c", cmd[pos]);
		if ((cmd[pos] == '|' && !current_quote) || cmd[pos + 1] == '\0')
		{
			if (!handle_command_processing(cmd, pipeline, &cmd_count, pos))
			{
				free_pipeline(pipeline);
				return ;
			}
			cmd_count++;
		}
		handle_quotes(cmd[pos], &current_quote);
	}
	pipeline->commands[cmd_count] = NULL;
}

t_pipeline	*split_command(char *cmd)
{
	t_pipeline	*pipeline;

	pipeline = init_pipeline(cmd);
	if (!pipeline)
		return (NULL);
	process_commands(cmd, pipeline);
	if (!pipeline->commands)
		return (NULL);
	return (pipeline);
}
