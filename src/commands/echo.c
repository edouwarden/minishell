/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:43:21 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/31 16:09:46 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	is_und_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **arg)
{
	int		i;
	int		old_i;
	char	n;
	int		c;

	i = 1;
	n = 0;
	c = get_c(arg);
	if (!arg || c == 1)
		return (0);
	while (is_und_n(arg[i]) && (i < c - 1))
		i++;
	if (i == 1)
		n = '\n';
	old_i = i;
	while (i < c - 1)
	{
		printf("%s ", arg[i]);
		i++;
	}
	if (old_i == i)
		return (0);
	printf("%s", arg[i]);
	printf("%c", n);
	return (0);
}

/*int main(int c, char **v)
{
  if (c > 1)
	echo(v);
  return (0);
}*/
