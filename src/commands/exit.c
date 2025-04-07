/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:07:56 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/07 15:26:24 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isnum(char *str)
{
	if (!str || !(*str))
		return (0);
	if ((*str < '0' || *str > '9') && *str != '-' && *str != '+')
		return (0);
	++str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long long	get_exit_status(char **args, t_env **env)
{
	long long	status;

	status = 0;
	if (!args || !args[1])
		return (atoi((*env)->value));
	if (args[2] && *args[2])
	{
		handle_too_many_args_error();
		return (1);
	}
	if (!ft_isnum(args[1]))
	{
		handle_non_numeric_arg_error(args[1]);
		return (2);
	}
	if (ft_strcmp(args[1], "9223372036854775807") > 0)
	{
		handle_exit_error(args[1]);
		return (2);
	}
	status = ft_atoi(args[1]);
	if (status < 0)
		return (156);
	return (status);
}
