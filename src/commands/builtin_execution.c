/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:28 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 11:07:29 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, CMD_ECHO) || !ft_strcmp(cmd, CMD_CD)
		|| !ft_strcmp(cmd, CMD_PWD) || !ft_strcmp(cmd, CMD_EXPORT)
		|| !ft_strcmp(cmd, CMD_UNSET) || !ft_strcmp(cmd, CMD_ENV)
		|| !ft_strcmp(cmd, CMD_EXIT));
}

void	execute_builtin(char **args, t_env **env)
{
	int	long long value;

	if (!args || !args[0])
		return ;
	value = -1;
	if (!ft_strcmp(args[0], CMD_ECHO))
		value = echo(args);
	else if (!ft_strcmp(args[0], CMD_CD))
		value = cd(args, env);
	else if (!ft_strcmp(args[0], CMD_PWD))
		value = pwd();
	else if (!ft_strcmp(args[0], CMD_EXPORT))
		value = ft_export(args, env);
	else if (!ft_strcmp(args[0], CMD_UNSET))
		value = ft_unset(args, env);
	else if (!ft_strcmp(args[0], CMD_ENV))
		value = print_env(args, env);
	else if (!ft_strcmp(args[0], CMD_EXIT))
		value = ft_exit(args, env);
	update_last_value(env, value);
}
