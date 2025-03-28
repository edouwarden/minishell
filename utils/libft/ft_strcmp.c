/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:29:53 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/11 16:52:31 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}

/*void main(int c, char **t)
{
	if (c == 3)
	{
		printf("%d", ft_strcmp(t[1],t[2]));
	}
}*/
