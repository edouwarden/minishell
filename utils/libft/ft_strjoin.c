/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:04:24 by enormand          #+#    #+#             */
/*   Updated: 2024/11/19 20:09:05 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char *ft_strjoin(const char *s1, const char *s2)
{
  char *str;

  if (!s1 && !s2)
    return (NULL);
  if (!s1)
    s1 = "";
  if (!s2)
    s2 = "";
  str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
  if (!str)
    return (NULL);
  ft_strlcpy(str, s1, ft_strlen(s1) + 1);
  ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
  return (str);
}
