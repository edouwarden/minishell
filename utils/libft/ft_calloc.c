/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:31:32 by enormand          #+#    #+#             */
/*   Updated: 2024/11/18 14:16:10 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(int count, int size)
{
	void	*p;

	p = ft_gc_malloc(count * size);
	if (p == 0)
		return (0);
	ft_bzero(p, count * size);
	return (p);
}
