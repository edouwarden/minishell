#include "../../include/minishell.h"
#include "../../include/env.h"

int is_builtin(char *cmd)
{
  return (!strcmp(cmd, CMD_ECHO) || !strcmp(cmd, CMD_CD) ||
          !strcmp(cmd, CMD_PWD) || !strcmp(cmd, CMD_EXPORT) ||
          !strcmp(cmd, CMD_UNSET) || !strcmp(cmd, CMD_ENV) ||
          !strcmp(cmd, CMD_EXIT));
}

void execute_builtin(char **args, t_env **env)
{
  int value;

  if (!args || !args[0])
    return;

  // Exécute la commande builtin appropriée
  value = -1;
  if (!strcmp(args[0], CMD_ECHO))
    value = echo(args);
  else if (!strcmp(args[0], CMD_CD))
    value = cd(args, env);
  else if (!strcmp(args[0], CMD_PWD))
    value = pwd();
  else if (!strcmp(args[0], CMD_EXPORT))
    value = ft_export(args, env);
  else if (!strcmp(args[0], CMD_UNSET))
    value = ft_unset(args, env);
  else if (!strcmp(args[0], CMD_ENV))
    value = print_env(env);
  else if (!strcmp(args[0], CMD_EXIT))
    exit(get_exit_status(args));
  update_last_value(env, value);
}
