/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:00:00 by enormand          #+#    #+#             */
/*   Updated: 2024/04/10 10:00:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "env.h"

typedef struct s_command
{
	char		**args;
	int			pipe_read;
	int			pipe_write;
	int			input_fd;
	int			output_fd;
	char		*input_file;
	char		*output_file;
	char		*heredoc_delim;
	int			append_mode;
}				t_command;

typedef struct s_pipeline
{
	t_command	**commands;
	int			cmd_count;
	t_env		**env;
	int			*pipe_fds;
}				t_pipeline;

// Command execution functions
int				is_builtin(char *cmd);
void			execute_builtin(char **args, t_env **env);
char			*find_command_path(char *cmd, char **env);
char			**get_paths(char **env);
char			*join_path(char *path, char *cmd);

// Command parsing functions
t_pipeline		*split_command(char *cmd);
t_command		*create_command(char **args);
char			**split_args(char *cmd, int start, int end);
int				count_pipes(char *cmd);
void			handle_quotes(char current_char, char *current_quote);
int				count_commands(char *cmd);

// Memory management
void			free_commands(t_command **commands, int count);
void			free_pipeline(t_pipeline *pipeline);
void			free_array(char **arr);

#endif