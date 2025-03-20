#include "../include/minishell.h"
#include "../include/env.h"

int	main(void)
{
	char		*cmd_line;
	t_env		**env;
	t_pipeline	*pipeline;

	env = create_env();
	// Configure Ctrl+C, Ctrl+D [input_handling.c]
	setup_signals();
	while (1)
	{
		// Lit la ligne de commande [input_handling.c]
		cmd_line = read_command_line();
		// Gere Ctrl+D [input_handling.c]
		handle_eof(cmd_line);
		cmd_line = dollex(cmd_line, env);
		
		if (cmd_line && *cmd_line)
		{
			// [parsing/command_split.c]
			pipeline = split_command(cmd_line);
			/*int x =0;
			while(pipeline->commands[0]->args[x] != 0)
				printf("%s - ",pipeline->commands[0]->args[x++]);
			printf("\n");*/
			/*
			t_pipeline {
				cmd_count = 2,                    // 2 commandes séparées par un pipe
				commands = [                      // Tableau de t_command*
					t_command {                   // Première commande
						args = [                  // Tableau de char*
							"/bin/echo",          // args[0]
							"hello world",        // args[1]
							NULL                  // Fin du tableau
						],
						pipe_read = -1,          // Pas de pipe en entrée
						pipe_write = 3,          // Écriture vers le pipe (fd hypothétique)
						input_fd = 0,            // STDIN standard
						output_fd = 1            // STDOUT standard
					},
					t_command {                  // Deuxième commande
						args = [                 // Tableau de char*
							"wc",               // args[0]
							"-l",              // args[1]
							NULL               // Fin du tableau
						],
						pipe_read = 2,         // Lecture depuis le pipe (fd hypothétique)
						pipe_write = -1,       // Pas de pipe en sortie
						input_fd = 0,         // STDIN standard
						output_fd = 1         // STDOUT standard
					},
					NULL                     // Fin du tableau de commandes
				],
				envp = (pointeur vers les variables d'environnement),
				pipe_fds = [2, 3]           // Les file descriptors des pipes
			}
			*/
			if (pipeline)
			{
				pipeline->env = env;
				// Exécute le pipeline [parsing/pipeline_execution.c]
				execute_pipeline(pipeline);
				// Libère la mémoire [error_handler.c]
				free_pipeline(pipeline);
			}
		}
		free(cmd_line);
	}
	return (0);
}
