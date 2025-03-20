/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:16:41 by enormand          #+#    #+#             */
/*   Updated: 2024/11/20 15:16:44 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *inside, const char *find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	first;

	if (!inside && len == 0)
		return (NULL);
	if (!*find)
		return ((char *)inside);
	i = 0;
	while (inside[i])
	{
		if (inside[i] == find[0])
		{
			j = 0;
			first = i;
			while (inside[i + j] && find[j] && inside[i + j] == find[j] && (i
					+ j) < len)
				j++;
			if (!find[j])
				return ((char *)&inside[first]);
		}
		i++;
	}
	return (NULL);
}
