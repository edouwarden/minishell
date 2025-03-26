/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:46:08 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/21 13:41:56 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

t_env	*is_in_env(t_env **env, char *name)
{
	t_env	*ptr;

	ptr = (*env)->next;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, name) == 0)
		{
			free(name);
			return (ptr);
		}
		ptr = ptr->next;
	}
	free(name);
	return (NULL);
}

void	del_one_env(t_env *ptr)
{
	free(ptr->name);
	free(ptr->value);
	free(ptr);
}

void	out_of_env(t_env **env, char *name)
{
	t_env	*ptr;
	t_env	*ptr_prev;

	ptr = (*env)->next;
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

void	ft_unset(char **v, t_env **env)
{
	int		c;
	int		i;

	c = get_c(v);
	if (c == 0)
		print_env(env);
	i = 1;
	while (i < c)
	{
		out_of_env(env, v[i]);
		i++;
	}
}
