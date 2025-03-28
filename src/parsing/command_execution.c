#include "../../include/env.h"
#include "../../include/minishell.h"

int is_builtin(char *cmd)
{
  if (!cmd)
    return (0);
  return (!strcmp(cmd, CMD_ECHO) || !strcmp(cmd, CMD_CD) || !strcmp(cmd, CMD_PWD) || !strcmp(cmd, CMD_EXPORT) || !strcmp(cmd, CMD_UNSET) || !strcmp(cmd, CMD_ENV) || !strcmp(cmd, CMD_EXIT));
}

int execute_builtin(char **args, t_env **env)
{
  if (!args || !args[0])
    return (0);
  // Exécute la commande builtin appropriée
  if (!strcmp(args[0], CMD_ECHO))
    return (echo(args));
  else if (!strcmp(args[0], CMD_CD))
    return (cd(args, env));
  else if (!strcmp(args[0], CMD_PWD))
    return (pwd());
  else if (!strcmp(args[0], CMD_EXPORT))
    return (ft_export(args, env), 0);
  else if (!strcmp(args[0], CMD_UNSET))
    return (ft_unset(args, env), 0);
  else if (!strcmp(args[0], CMD_ENV))
    return (print_env(env), 0);
  else if (!strcmp(args[0], CMD_EXIT))
    exit(get_exit_status(args + 1));
  return (0);
}
