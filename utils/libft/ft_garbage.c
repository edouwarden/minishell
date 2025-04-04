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

typedef struct s_garbage
{
  void *ptr;
  struct s_garbage *next;
} t_garbage;

static t_garbage *g_garbage_list = NULL;

void *ft_gc_malloc(size_t size)
{
  void *ptr;
  t_garbage *new;

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
  new->next = g_garbage_list;
  g_garbage_list = new;

  return (ptr);
}

void ft_gc_free(void *ptr)
{
  t_garbage *current;
  t_garbage *prev;

  if (!ptr)
    return;
  current = g_garbage_list;
  prev = NULL;
  while (current)
  {
    if (current->ptr == ptr)
    {
      if (prev)
        prev->next = current->next;
      else
        g_garbage_list = current->next;
      free(current->ptr);
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
  free(ptr);
}

void ft_gc_cleanup(void)
{
  t_garbage *current;
  t_garbage *next;

  current = g_garbage_list;
  while (current)
  {
    next = current->next;
    free(current->ptr);
    free(current);
    current = next;
  }
  g_garbage_list = NULL;
}
