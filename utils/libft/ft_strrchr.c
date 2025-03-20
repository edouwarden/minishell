/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:32:44 by enormand          #+#    #+#             */
/*   Updated: 2025/01/29 13:30:28 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(s);
	if (!len)
		return (0);
	while (++i < len + 1)
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (0);
}
