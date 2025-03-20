/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:47:41 by enormand          #+#    #+#             */
/*   Updated: 2024/11/19 19:37:33 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;
	int		len;
	int		i;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 && !set)
		return (NULL);
	while (s1[start] && check(set, s1[start]))
		start++;
	while (start < end && check(set, s1[end - 1]))
		end--;
	len = end - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (end > start)
		ptr[i++] = s1[start++];
	ptr[i] = '\0';
	return (ptr);
}
