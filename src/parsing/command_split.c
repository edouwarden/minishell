/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:21 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 14:18:29 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pipeline	*split_command(char *cmd)
{
	t_pipeline	*pipeline;
	char		**current_args;
	int			current_pos;
	int			cmd_start;
	int			cmd_count;
	int			current_quote;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	cmd_count = 1;
	current_pos = 0;
	current_quote = 0;
	while (cmd[current_pos])
	{
		if (cmd[current_pos] == '|' && !current_quote)
			cmd_count++;
		if (cmd[current_pos] == '\'' || cmd[current_pos] == '"')
		{
			debug_printf("Quote found: %c", cmd[current_pos]);
			if (current_quote == cmd[current_pos])
				current_quote = 0;
			else
				current_quote = cmd[current_pos];
		}
		current_pos++;
	}
	pipeline->commands = ft_calloc(cmd_count + 1, sizeof(t_command *));
	pipeline->cmd_count = cmd_count;
	if (!pipeline->commands)
	{
		ft_gc_free(pipeline);
		return (NULL);
	}
	current_pos = 0;
	cmd_start = 0;
	cmd_count = 0;
	current_quote = 0;
	while (cmd[current_pos])
	{
		if ((cmd[current_pos] == '|' && !current_quote) || cmd[current_pos
			+ 1] == '\0')
		{
			current_args = split_args(cmd, cmd_start, cmd[current_pos
					+ 1] == '\0' ? current_pos + 1 : current_pos);
			/* Debug*/
			debug_str_list(current_args);
			if (!current_args || !*current_args)
			{
				free_pipeline(pipeline);
				return (NULL);
			}
			pipeline->commands[cmd_count] = create_command(current_args);
			if (!pipeline->commands[cmd_count])
			{
				free_array(current_args);
				free_pipeline(pipeline);
				return (NULL);
			}
			pipeline->commands[cmd_count]->args = process_redirections(pipeline->commands[cmd_count],
					current_args);
			if (!pipeline->commands[cmd_count]->args)
			{
				free_pipeline(pipeline);
				return (NULL);
			}
			cmd_count++;
			cmd_start = current_pos + 1;
		}
		if (cmd[current_pos] == '\'' || cmd[current_pos] == '"')
		{
			debug_printf("Quote found: %c", cmd[current_pos]);
			if (current_quote == cmd[current_pos])
				current_quote = 0;
			else
				current_quote = cmd[current_pos];
		}
		current_pos++;
	}
	pipeline->commands[cmd_count] = NULL;
	return (pipeline);
}
