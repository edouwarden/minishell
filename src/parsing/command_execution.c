#include "../../include/minishell.h"
#include "../../include/env.h"

int	is_builtin(char *cmd)
{
	return (!strcmp(cmd, CMD_ECHO) || !strcmp(cmd, CMD_CD) ||
			!strcmp(cmd, CMD_PWD) || !strcmp(cmd, CMD_EXPORT) ||
			!strcmp(cmd, CMD_UNSET) || !strcmp(cmd, CMD_ENV) ||
			!strcmp(cmd, CMD_EXIT));
}

void	execute_builtin(char **args, t_env **env)
{
	if (!args || !args[0])
		return ;
	
	// Exécute la commande builtin appropriée
	if (!strcmp(args[0], CMD_ECHO))
		echo(args);
	else if (!strcmp(args[0], CMD_CD))
		printf("TODO: Implement cd\n");
	else if (!strcmp(args[0], CMD_PWD))
		printf("TODO: Implement pwd\n");
	else if (!strcmp(args[0], CMD_EXPORT))
		ft_export(args, env);
	else if (!strcmp(args[0], CMD_UNSET))
		ft_unset(args, env);
	else if (!strcmp(args[0], CMD_ENV))
		print_env(env);
	else if (!strcmp(args[0], CMD_EXIT))
		exit(0); //TODO
}
