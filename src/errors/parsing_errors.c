/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:51:04 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 14:04:53 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_parse_error(char *c)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near `", STDERR);
	ft_putstr_fd(c, STDERR);
	ft_putstr_fd("'\033[0m\n", STDERR);
}

void	handle_newline_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near newline\033[0m\n",
		STDERR);
}
