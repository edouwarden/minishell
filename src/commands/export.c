/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:22:51 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/31 14:54:52 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	is_egal(char *str)
{
	int	i;
	int first_equal;
	
	if (ft_isalpha(str[0]) != 1 && str[0] != '_')
		return (-1);
	i = 1;
	first_equal = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_' && str[i] != '=')
				return (-1);
		}
		if (str[i] == '=' && first_equal == 0)
			first_equal = i;
		i++;
	}
	if (first_equal == 1 && str[0] == '_')
		return -1;
	return (0);
}

void	add_to(t_env **env, char *var)
{
	t_env	*tmp;

	tmp = new_env(get_n(var), get_v(var));
	if (!tmp)
		return ;
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

int	ft_export(char **v, t_env **env)
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
			return (1);
		i++;
	}
	i = 1;
	while (i < c)
	{
			element = is_in_env(env, get_n(v[i]));
			if (element)
			{
				if (element->value)
					free(element->value);
				element->value = get_v(v[i]);
			}
			else
				add_to(env, v[i]);
		i++;
	}
	return (0);
}
