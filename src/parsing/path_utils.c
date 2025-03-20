#include "../../include/minishell.h"

char	*join_path(char *path, char *cmd)
{
	char	*full_path;
	int		path_len;
	int		cmd_len;

	// Calcule la taille totale du chemin
	path_len = strlen(path);
	cmd_len = strlen(cmd);
	full_path = ft_calloc(path_len + cmd_len + 2, sizeof(char));
	if (!full_path)
		return (NULL);
	// Construit le chemin complet (path/cmd)
	strcpy(full_path, path);
	full_path[path_len] = '/';
	strcpy(full_path + path_len + 1, cmd);
	return (full_path);
}

char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	// Cherche la variable PATH dans l'environnement
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			// Divise le PATH en tableau [libft/ft_split.c]
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	// Si chemin absolu ou relatif
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			// Duplique la chaîne [libft/ft_strdup.c]
			return (ft_strdup(cmd));
		return (NULL);
	}
	// Cherche dans les dossiers du PATH [get_paths ci-dessus]
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		// Construit le chemin complet [join_path ci-dessus]
		cmd_path = join_path(paths[i], cmd);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
		{
			// Libère le tableau de chemins [error_handler.c]
			free_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
} 