/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:00:00 by enormand          #+#    #+#             */
/*   Updated: 2024/04/10 10:00:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "commands.h"

# define REDIR_IN "<"
# define REDIR_OUT ">"
# define REDIR_HEREDOC "<<"
# define REDIR_APPEND ">>"

// Core redirection functions
char	**process_redirections(t_command *cmd, char **args);
int		handle_redirection_token(t_command *cmd, char **args, int *i);

int		handle_heredoc(t_command *cmd);
int		handle_input_redirection(t_command *cmd);
int		handle_output_redirection(t_command *cmd);

// Utility functions
int		handle_redirection_error(char *token, char *next_arg);
int		is_redirection_token(char *token);
void	cleanup_old_args(char **args);
char	**allocate_new_args(int count);
int		count_non_redirection_args(char **args);

// Execution redirection functions
void	cleanup_heredoc_file(void);
void	cleanup_redirections(t_command *cmd);

#endif