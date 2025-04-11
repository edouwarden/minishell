/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:00:33 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	ft_strncpy(char *src, char *dest, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*get_n(char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	tmp = (char *) ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (NULL);
	ft_strncpy(env, tmp, i);
	return (tmp);
}

char	*get_v(char *env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (env[i] != '=' && env[i])
		i++;
	len = ft_strlen(env);
	if (i == len)
		return (NULL);
	tmp = (char *) ft_calloc(sizeof(char), (len - i) + 1);
	if (!tmp)
		return (NULL);
	ft_strncpy(env + i + 1, tmp, len - i);
	return (tmp);
}
