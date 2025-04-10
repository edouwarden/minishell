/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching_things.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:10 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/09 11:37:52 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../include/minishell.h"

int	is_stop(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*is_in_env_bis(char *var, t_env **env)
{
	char	*final;
	t_env	*ptr;

	final = NULL;
	if (!var || var[0] == 0)
		return (ft_strdup("$"));
	if (var[0] == '?')
		return ((**env).value);
	if (strcmp("\'", var) == 0)
		return (ft_strdup("$"));
	if (strcmp("\"", var) == 0)
		return (ft_strdup("$"));
	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(var, ptr->name) == 0)
			final = ptr->value;
		ptr = ptr->next;
	}
	ft_gc_free(var);
	return (final);
}

char	*search_dollex(char *str, int i, t_env **env)
{
	int		len;
	char	*var;
	char	*final;
	char	*dollex;

	len = 0;
	while (is_stop(str[i]))
	{
		len++;
		i++;
	}
	if (len == 0 && str[i] == '?')
	{
		i++;
		len++;
	}
	var = ft_calloc(len + 1, sizeof(char));
	ft_strncpy(str + i - len, var, len);
	final = is_in_env_bis(var, env);
	dollex = add_final(i, len, str, final);
	return (dollex);
}
