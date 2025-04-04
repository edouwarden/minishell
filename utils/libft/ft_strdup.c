/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:01:46 by enormand          #+#    #+#             */
/*   Updated: 2024/11/18 15:01:50 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *s1)
{
  int s1_len;
  char *dup;

  s1_len = ft_strlen(s1);
  dup = (char *)ft_calloc(s1_len + 1, sizeof(char));
  if (!dup)
    return (NULL);
  dup[s1_len] = 0;
  while (--s1_len >= 0)
    dup[s1_len] = s1[s1_len];
  return (dup);
}
