/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:20:00 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 12:46:52 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gc_node	**get_gc_list(void)
{
	static t_gc_node	*gc_list = NULL;

	return (&gc_list);
}

void	*ft_gc_malloc(size_t size)
{
	void		*ptr;
	t_gc_node	*new;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_gc_node));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *get_gc_list();
	*get_gc_list() = new;
	return (ptr);
}

void	ft_gc_free(void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!ptr)
		return ;
	current = *get_gc_list();
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*get_gc_list() = current->next;
			free(ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_gc_normal_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_gc_cleanup(void)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = *get_gc_list();
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*get_gc_list() = NULL;
}
