/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:58:32 by enormand          #+#    #+#             */
/*   Updated: 2024/11/19 19:28:40 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(long long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(long long n)
{
	char		*ptr;
	int			len;
	long long	i;

	i = (long long)n;
	len = ft_count_digits(i);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if (n == 0)
		ptr[0] = '0';
	if (i < 0)
	{
		i *= -1;
		ptr[0] = '-';
	}
	while (len > 0 && i > 0)
	{
		ptr[len - 1] = i % 10 + '0';
		i /= 10;
		len--;
	}
	len = ft_count_digits(n);
	ptr[len] = '\0';
	return (ptr);
}
