/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:46:30 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:20 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include "commands.h"
# include "env.h"
# include "input.h"
# include "redirections.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

# define CMD_ECHO "echo"
# define CMD_CD "cd"
# define CMD_PWD "pwd"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define CMD_ENV "env"
# define CMD_EXIT "exit"

// Exit status
long long	get_exit_status(char **args, t_env **env);

// Pipeline execution
void		execute_pipeline(t_pipeline *pipeline);
void		execute_piped_command(t_command *cmd, t_env **envp);
void		handle_builtin_single_command(t_pipeline *pipeline);
void		wait_for_children(pid_t *child_pids, int cmd_count, t_env **env);

// Redirections
void		handle_pipe_redirections(t_command *cmd);
void		handle_file_redirections(t_command *cmd);
void		handle_redirections(t_command *cmd);

#endif
