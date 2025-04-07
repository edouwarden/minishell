/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:20:00 by enormand          #+#    #+#             */
/*   Updated: 2024/11/18 14:20:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_garbage	**get_garbage(void)
{
	static t_garbage	*garbage_list = NULL;

	return (&garbage_list);
}

void	*ft_gc_malloc(size_t size)
{
	void		*ptr;
	t_garbage	*new;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *get_garbage();
	*get_garbage() = new;
	return (ptr);
}

void	ft_gc_free(void *ptr)
{
	t_garbage	*current;
	t_garbage	*prev;

	if (!ptr)
		return ;
	current = *get_garbage();
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*get_garbage() = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
}

void	ft_gc_cleanup(void)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *get_garbage();
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*get_garbage() = NULL;
}
