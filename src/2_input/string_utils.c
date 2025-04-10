/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 11:45:23 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/env.h"
#include "../../include/minishell.h"

char	*concat(const char **strs, int count)
{
	char	*result;
	char	*temp;
	int		i;

	if (!strs || count <= 0)
		return (NULL);
	if (!strs[0])
		result = ft_strdup("");
	else
		result = ft_strdup(strs[0]);
	if (!result)
		return (NULL);
	i = 0;
	while (++i < count)
	{
		if (!strs[i])
			temp = ft_strjoin(result, "");
		else
			temp = ft_strjoin(result, strs[i]);
		ft_gc_free(result);
		if (!temp)
			return (NULL);
		result = temp;
	}
	return (result);
}

char	*get_relative_path(const char *path, const char *home)
{
	const char	*relative;
	char		*result;

	relative = path + ft_strlen(home);
	if (ft_strncmp(path, home, ft_strlen(home)) != 0)
	{
		return (ft_strdup(path));
	}
	while (*relative == '/')
	{
		relative++;
	}
	if (*relative == '\0')
	{
		return (ft_strdup("~"));
	}
	result = ft_strjoin("~/", relative);
	return (result);
}
