/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_absolute_path(t_command *cmd, char **env)
{
	char	*command_path;

	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == -1)
		{
			print_permission_errors(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(126);
		}
		command_path = ft_strdup(cmd->args[0]);
	}
	else
	{
		print_command_error(cmd->args[0]);
		free_array(env);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(127);
	}
	return (command_path);
}

static char	*get_command_path(t_command *cmd, char **env)
{
	char	*command_path;

	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		command_path = handle_absolute_path(cmd, env);
	else
	{
		command_path = find_command_path(cmd->args[0], env);
		if (!command_path)
		{
			print_command_error(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(127);
		}
	}
	return (command_path);
}

static void	execute_builtin_command(t_command *cmd, t_env **envp, int status)
{
	execute_builtin(cmd->args, envp);
	cleanup_redirections(cmd);
	ft_gc_cleanup();
	exit(status);
}

static void	execute_external_command(t_command *cmd, t_env **envp)
{
	char	*command_path;
	char	**env;
	int		status;

	env = convert_env_to_array(envp);
	if (!env)
	{
		perror("Failed to create environment array");
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	command_path = get_command_path(cmd, env);
	status = execve(command_path, cmd->args, env);
	if (status == -1)
	{
		perror("execve: command execution failed");
		ft_gc_free(command_path);
		free_array(env);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(126);
	}
}

void	execute_piped_command(t_command *cmd, t_env **envp)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_redirections(cmd);
	if (!cmd->args[0])
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_SUCCESS);
	}
	handle_pipe_redirections(cmd);
	handle_file_redirections(cmd);
	if (is_builtin(cmd->args[0]))
		execute_builtin_command(cmd, envp, status);
	execute_external_command(cmd, envp);
}
