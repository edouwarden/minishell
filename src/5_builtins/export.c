/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:22:51 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int	is_egal(char *str)
{
	int	i;
	int	first_equal;

	if (ft_isalpha(str[0]) != 1 && str[0] != '_')
		return (-1);
	i = 1;
	first_equal = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if ((str[i] != '_' && str[i] != '='))
				return (-1);
		}
		if (str[i] == '=')
		{
			if (first_equal == 1 && str[0] == '_')
				return (-1);
			return (i);
		}
		i++;
	}
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

int	check_args(char **v, int c)
{
	int	i;

	i = 1;
	while (i < c)
	{
		if (is_egal(v[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char **v, t_env **env)
{
	int		c;
	int		i;
	t_env	*element;

	c = get_c(v);
	if (c == 1)
		print_env(v, env);
	if (check_args(v, c))
		return (1);
	i = 1;
	while (i < c)
	{
		element = is_in_env(env, get_n(v[i]));
		if (element)
		{
			if (element->value)
				ft_gc_free(element->value);
			element->value = get_v(v[i]);
		}
		else
			add_to(env, v[i]);
		i++;
	}
	return (0);
}
