/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:46:30 by enormand          #+#    #+#             */
/*   Updated: 2024/11/08 14:20:41 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_contain_any(char *str, char c)
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

long long	ft_atoi(char *str)
{
	int			i;
	long long	res;
	int			minus;

	i = 0;
	res = 0;
	minus = 0;
	while (ft_contain_any(" \t\v\r\f\n", str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - '0');
		i++;
	}
	if (minus % 2 == 0)
		return (res);
	else
		return (res * -1);
}
