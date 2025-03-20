/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:46:30 by enormand          #+#    #+#             */
/*   Updated: 2025/03/04 14:52:26 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"
# include "env.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
** Built-in Commands
*/
# define CMD_ECHO "echo"
# define CMD_CD "cd"
# define CMD_PWD "pwd"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define CMD_ENV "env"
# define CMD_EXIT "exit"

/*
** Structures
*/
typedef struct s_command
{
	char	**args;
	int		pipe_read;
	int		pipe_write;
	int		input_fd;
	int		output_fd;
}	t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			cmd_count;
	t_env		**env;
	int			*pipe_fds;
}	t_pipeline;

/*
** Function Prototypes
*/

/* Signal and input handling */
void		setup_signals(void);
void		handle_sigint(int sig);
char		*read_command_line(void);
void		handle_eof(char *line);

/* Error handling and memory management */
void		free_array(char **arr);
void		handle_memory_error(void);
void		handle_command_error(char *cmd);
void		free_commands(t_command **commands, int count);
void		free_pipeline(t_pipeline *pipeline);

/* Command processing */
t_pipeline	*split_command(char *cmd);
t_command	*create_command(char **args);

/* Command execution */
int			is_builtin(char *cmd);
void		execute_builtin(char **args, t_env **env);
int			execute_pipeline(t_pipeline *pipeline);

/* Path handling */
char		*find_command_path(char *cmd, char **env);
char		**get_paths(char **env);
char		*join_path(char *path, char *cmd);

# endif
