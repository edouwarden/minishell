/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:50:45 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 12:07:53 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exit_error(char *arg)
{
	ft_putstr_fd("\033[0;31m❌ minishell: exit: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": numeric argument required\033[0m\n", STDERR);
}

void	print_too_many_args_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: too many arguments\033[0m\n", STDERR);
}

void	print_non_numeric_arg_error(char *arg)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": numeric argument required\033[0m\n", STDERR);
}

void	print_open_error(char *file, int error_code)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	if (error_code == EACCES)
		ft_putstr_fd(": Permission denied\033[0m\n", STDERR);
	else
		ft_putstr_fd(": Error opening file\033[0m\n", STDERR);
}
