/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:40 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 11:26:39 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env.h"
#include "../include/minishell.h"

int	main(void)
{
	char		*cmd_line;
	t_env		**env;
	t_pipeline	*pipeline;

	env = create_env();
	setup_signals();
	while (1)
	{
		cmd_line = read_command_line(env);
		handle_eof(cmd_line);
		cmd_line = dollex(cmd_line, env);
		if (cmd_line && *cmd_line)
		{
			pipeline = split_command(cmd_line);
			if (pipeline)
			{
				pipeline->env = env;
				execute_pipeline(pipeline);
				free_pipeline(pipeline);
			}
		}
		ft_gc_free(cmd_line);
	}
	return (0);
}
