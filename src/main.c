/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:40 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 11:06:41 by enormand         ###   ########.fr       */
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
			/*int x =0;
			while(pipeline->commands[0]->args[x] != 0)
				printf("%s - ",pipeline->commands[0]->args[x++]);
			printf("\n");*/
			/*
			t_pipeline {
				cmd_count = 2,
				commands = [
				t_command {
				args = [
				"/bin/echo",
				"hello world",
				NULL
				],
				pipe_read = -1,
				pipe_write = 3,
				input_fd = 0,
				output_fd = 1
				},
				t_command {
				args = [
				"wc",
				"-l",
				NULL
				],
				pipe_read = 2,
				pipe_write = -1,
				input_fd = 0,
				output_fd = 1
				},
				NULL
				],
				envp = (pointeur vers les variables d'environnement),
				pipe_fds = [2, 3]
			}
			*/
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
