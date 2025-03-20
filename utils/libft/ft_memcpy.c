/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:46:47 by enormand          #+#    #+#             */
/*   Updated: 2024/11/19 22:57:39 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*pt;
	size_t				i;

	p = (unsigned char *)dst;
	pt = (const unsigned char *)src;
	i = 0;
	if (!p && !pt)
		return (NULL);
	while (i < n)
	{
		p[i] = pt[i];
		i++;
	}
	return (dst);
}
