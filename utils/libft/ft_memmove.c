/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:19:53 by enormand          #+#    #+#             */
/*   Updated: 2024/11/20 13:00:57 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*p_dst;
	const char	*p_src;
	size_t		i;

	p_dst = (char *)dst;
	p_src = (const char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (p_src >= p_dst || p_dst >= len + p_src)
	{
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	else
	{
		while (len--)
		{
			p_dst[len] = p_src[len];
		}
	}
	return (dst);
}
