/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:43:21 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/20 11:52:15 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int is_und_n(char *str)
{
	int i;

	
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

int echo(char **arg)
{
	int i;
	char n;
	int c;

	i = 1;
	n = 0;
	c = get_c(arg);
	if (!arg || c == 1)
		return (0);
	while (is_und_n(arg[i]) && (i < c))
		i++;
	if (i == 1) 
		n = '\n';
	while (i < c)
	{
		printf("%s",arg[i]);
		i++;
	}
	printf("%c",n);
	return(0);
}

/*int main(int c, char **v)
{
	if (c > 1)
		echo(v);
	return (0);
}*/
