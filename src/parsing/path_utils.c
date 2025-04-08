/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:12 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 12:34:01 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_path(char *path, char *cmd)
{
	char	*full_path;
	int		path_len;
	int		cmd_len;

	if (!path || !cmd)
		return (NULL);
	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full_path = ft_calloc(path_len + cmd_len + 2, sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	full_path[path_len] = '/';
	ft_strcpy(full_path + path_len + 1, cmd);
	return (full_path);
}

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*check_each_path(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = join_path(paths[i], cmd);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (cmd_path);
		}
		ft_gc_free(cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;

	if (!cmd || !envp)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	return (check_each_path(paths, cmd));
}
