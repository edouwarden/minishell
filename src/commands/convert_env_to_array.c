/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:39:14 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/07 15:48:49 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	get_env_len(t_env **env)
{
	t_env	*ptr;
	int		i;

	ptr = (*env)->next;
	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	free_array_env(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_gc_free(array[i]);
		i++;
	}
	ft_gc_free(array[i]);
	ft_gc_free(array);
}

char	*create_str_env(t_env *node)
{
	int		len_name;
	int		len_value;
	char	*resu;

	if (!node)
		return (NULL);
	len_name = ft_strlen(node->name);
	len_value = ft_strlen(node->value);
	resu = ft_calloc(len_value + len_name + 2, sizeof(char));
	if (!resu)
		return (NULL);
	ft_strcpy(resu, node->name);
	resu[len_name] = '=';
	ft_strcpy(resu + len_name + 1, node->value);
	return (resu);
}

char	**convert_env_to_array(t_env **env)
{
	int		len;
	int		i;
	char	**array;
	t_env	*ptr;

	i = 1;
	if (!env)
		return (NULL);
	len = get_env_len(env);
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	ptr = (*env)->next;
	array[0] = create_str_env(ptr);
	while (ptr)
	{
		ptr = ptr->next;
		array[i] = create_str_env(ptr);
		i++;
	}
	return (array);
}
