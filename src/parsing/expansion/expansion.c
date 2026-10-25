/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:10 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

char	*replace_variable(int i, int len_name, char *str, char *value)
{
	int		len_str;
	int		len_value;
	int		j;
	int		k;
	char	*resu;

	len_str = ft_strlen(str);
	len_value = ft_strlen(value);
	resu = ft_calloc((len_str + len_value - len_name + 1), sizeof(char));
	j = 0;
	while (j < i - (len_name + 1))
	{
		resu[j] = str[j];
		j++;
	}
	k = 0;
	while (k < len_value)
	{
		resu[j] = value[k];
		k++;
		j++;
	}
	ft_strcpy(resu + j, str + i);
	ft_gc_free(str);
	return (resu);
}

void	handle_quote(char c, char *str, int *i, int *quote)
{
	if (c == '\'' && *quote == 0)
	{
		*i = *i + 1;
		while (str[*i] && str[*i] != '\'')
			*i = *i + 1;
	}
	else if (c == '"')
		*quote = (*quote + 1) % 2;
}

char	*expand_variables(char *str, t_env **env)
{
	int		i;
	int		quote;
	char	*expanded;

	i = 0;
	quote = 0;
	expanded = ft_strdup(str);
	while (expanded[i])
	{
		if (expanded[i] == '\'' || expanded[i] == '"')
			handle_quote(expanded[i], expanded, &i, &quote);
		else if (expanded[i] == '$')
			expanded = expand_variable(expanded, i + 1, env);
		i++;
	}
	ft_gc_free(str);
	return (expanded);
}
