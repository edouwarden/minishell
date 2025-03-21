/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:10 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/21 12:48:04 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int	is_stop(char c)
{
	if (c == ' ')
		return (0);
	if (c == '$')
		return (0);
	if (c == '"')
		return (0);
	if (c == '\t')
		return (0);
	if (c == '\n')
		return (0);
	if (c == '|')
		return (0);
	if (c == '\0')
		return (0);
	if (c == '?')
		return (0);
	if (c == '.')
		return (0);
	return (1);
}

char	*add_final(int i, int len_name, char *str, char *value)
{
	int		len_str;
	int		len_value;
	int		j;
	int		k;
	char	*resu;

	len_str = ft_strlen(str);
	len_value = ft_strlen(value);
	resu = calloc((len_str + len_value - len_name + 1), sizeof(char));
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
	while (str[i])
	{	
		resu[j] = str[i];
		j++;
		i++;
	}
	free(str);
	return (resu);
}

char	*is_in_env_bis(char *var, t_env **env)
{
	char	*final;
	t_env	*ptr;

	final = NULL;
	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(var, ptr->name) == 0)
			final = ptr->value;
		ptr = ptr->next;
	}
	free(var);
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
	var = calloc(len + 1, sizeof(char));
	ft_strncpy(str + i - len, var, len);
	final = is_in_env_bis(var, env);
	dollex = add_final(i, len, str, final);
	return (dollex);
}

void	quote_management(char c, char *str, int *i, int *quote)
{
	
	if (c == '\'' && quote == 0)
	{
		while(str[*i] && str[*i] != '\'')
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
	with_dollex = strdup(str);
	while (with_dollex[i])
	{
		if (with_dollex[i] == '\'' || with_dollex[i] == '"')
			quote_management(with_dollex[i], with_dollex, &i, &quote);
		if (with_dollex[i] == '$')
		{
			with_dollex = search_dollex(with_dollex, i + 1, env);
			//i--;
			//printf("i apres search %d\n",i);
		}
		i++;
	}
	free(str);
	return (with_dollex);
}
