/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:46:08 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

t_env	*is_in_env(t_env **env, char *name)
{
	t_env	*ptr;

	ptr = (*env)->next;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, name) == 0)
		{
			ft_gc_free(name);
			return (ptr);
		}
		ptr = ptr->next;
	}
	ft_gc_free(name);
	return (NULL);
}

void	del_one_env(t_env *ptr)
{
	ft_gc_free(ptr->name);
	ft_gc_free(ptr->value);
	ft_gc_free(ptr);
}

void	remove_env_variable(t_env **env, char *name)
{
	t_env	*ptr;
	t_env	*ptr_prev;

	ptr = (*env);
	ptr_prev = ptr;
	ptr = ptr->next;
	if (ft_strcmp(ptr_prev->name, name) == 0)
	{
		*env = ptr;
		del_one_env(ptr_prev);
	}
	while (ptr)
	{
		if (ft_strcmp(ptr->name, name) == 0)
		{
			ptr_prev->next = ptr->next;
			del_one_env(ptr);
			return ;
		}
		ptr_prev = ptr;
		ptr = ptr->next;
	}
}

int	builtin_unset(char **v, t_env **env)
{
	int	c;
	int	i;

	c = count_strings(v);
	if (c == 0)
		return (0);
	i = 1;
	while (i < c)
	{
		if (v[i])
		{
			if (ft_strcmp("_", v[i]) != 0 || ft_strcmp("?", v[i]) != 0)
				remove_env_variable(env, v[i]);
		}
		i++;
	}
	return (0);
}
