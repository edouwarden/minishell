/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:22:51 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/19 15:39:47 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	is_egal(char *str)
{
	int	i;

	if (str[0] == '=')
		return (-1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	add_to(t_env **env, char *var)
{
	t_env	*tmp;

	tmp = new_env(get_n(var), get_v(var));
	if (!tmp)
	{
		printf("export: Memory allocation failed to add : `%s'", var);
		return ;
	}
	add_back_env(tmp, env);
}

int	get_c(char **v)
{
	int	i;

	i = 0;
	while (v[i])
		i++;
	return (i);
}

void	ft_export(char **v, t_env **env)
{
	int		c;
	int		i;
	t_env	*element;
	int		error_management;

	c = get_c(v);
	if (c == 0)
		print_env(env);
	i = 1;
	while (i < c)
	{
		error_management = is_egal(v[i]);
		if (error_management == -1)
			printf("export: `%s': not a valid identifier\n", v[i]);
		else
		{
			element = is_in_env(env, get_n(v[i]));
			if (element)
			{
				free(element->value);
				element->value = get_v(v[i]);
			}
			else
				add_to(env, v[i]);
		}
		i++;
	}
}
