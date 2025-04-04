#include "../../include/minishell.h"

char *join_path(char *path, char *cmd)
{
  char *full_path;
  int path_len;
  int cmd_len;

  if (!path || !cmd)
    return (NULL);
  path_len = strlen(path);
  cmd_len = strlen(cmd);
  full_path = ft_calloc(path_len + cmd_len + 2, sizeof(char));
  if (!full_path)
    return (NULL);
  strcpy(full_path, path);
  full_path[path_len] = '/';
  strcpy(full_path + path_len + 1, cmd);
  return (full_path);
}

char **get_paths(char **envp)
{
  char **paths;
  int i;

  if (!envp)
    return (NULL);
  i = 0;
  while (envp[i])
  {
    if (strncmp(envp[i], "PATH=", 5) == 0)
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

char *find_command_path(char *cmd, char **envp)
{
  char **paths;
  char *cmd_path;
  int i;

  if (!cmd || !envp)
    return (NULL);

  // Handle absolute or relative paths
  if (cmd[0] == '/' || cmd[0] == '.')
  {
    if (access(cmd, F_OK | X_OK) == 0)
      return (ft_strdup(cmd));
    return (NULL);
  }

  // Search in PATH directories
  paths = get_paths(envp);
  if (!paths)
    return (NULL);

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
