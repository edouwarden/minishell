/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:00:33 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

t_env	**env_backup(t_env **env)
{
	static t_env	**backup;

	if (env)
	{
		backup = env;
		return (backup);
	}
	return (backup);
}

void	add_back_env(t_env *new_env, t_env **lst)
{
	t_env	*ptr;

	if (!lst || !new_env)
	{
		*lst = new_env;
		return ;
	}
	ptr = ft_lstlast(*lst);
	if (!ptr)
	{
		*lst = new_env;
		return ;
	}
	ptr->next = new_env;
	new_env->next = NULL;
}

void	add_front_env(t_env *node, t_env **list)
{
	if (!node)
		return ;
	if (list)
		node->next = *list;
	*list = node;
}

t_env	*new_env(char *n, char *v)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!n || !v || !new_node)
	{
		if (n)
			ft_gc_free(n);
		if (v)
			ft_gc_free(v);
		if (new_node)
			ft_gc_free(new_node);
		return (NULL);
	}
	new_node->name = n;
	new_node->value = v;
	new_node->next = NULL;
	return (new_node);
}
