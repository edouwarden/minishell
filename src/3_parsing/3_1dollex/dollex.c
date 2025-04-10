/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:10 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/09 11:38:13 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/env.h"
#include "../../../include/minishell.h"

char	*add_final(int i, int len_name, char *str, char *value)
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

void	quote_management(char c, char *str, int *i, int *quote)
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

char	*dollex(char *str, t_env **env)
{
	int		i;
	int		quote;
	char	*with_dollex;

	i = 0;
	quote = 0;
	with_dollex = ft_strdup(str);
	while (with_dollex[i])
	{
		if (with_dollex[i] == '\'' || with_dollex[i] == '"')
			quote_management(with_dollex[i], with_dollex, &i, &quote);
		else if (with_dollex[i] == '$')
			with_dollex = search_dollex(with_dollex, i + 1, env);
		i++;
	}
	ft_gc_free(str);
	return (with_dollex);
}
