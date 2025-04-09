/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:51:04 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 10:37:58 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_parse_error(char *c)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near `", STDERR);
	ft_putstr_fd(c, STDERR);
	ft_putstr_fd("'\033[0m\n", STDERR);
}

void	print_newline_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near newline\033[0m\n",
		STDERR);
}

void	print_permission_errors(char *str)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": Permission denied\033[0m\n", STDERR);
}

void	print_not_found_errors(char *file)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": No such file or directory\033[0m\n", STDERR);
}
