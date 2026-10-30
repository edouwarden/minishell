/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:23:10 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 18:50:01 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

char	*set_shell_pid(char *pid_str)
{
	static char	*p_didy;

	if (pid_str == NULL)
		return (p_didy);
	p_didy = pid_str;
	return (NULL);
}

char	*get_shell_pid(void)
{
	char	*p_didy;

	kill(0, SIGUSR1);
	p_didy = set_shell_pid(NULL);
	return (p_didy);
}

int	is_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*find_env_value(char *var, t_env **env)
{
	char	*final;
	t_env	*ptr;

	final = NULL;
	if (!var || var[0] == 0)
		return (ft_strdup("$"));
	if (var[0] == '?')
		return ((**env).value);
	if (ft_strcmp("\'", var) == 0 || ft_strcmp("\"", var) == 0)
		return (ft_strdup("$"));
	if (var[0] == '$')
		return (get_shell_pid());
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

char	*expand_variable(char *str, int i, t_env **env)
{
	int		len;
	char	*var;
	char	*final;
	char	*expanded;

	len = 0;
	while (is_var_char(str[i]))
	{
		len++;
		i++;
	}
	if (len == 0 && (str[i] == '?' || str[i] == '$'))
	{
		i++;
		len++;
	}
	var = ft_calloc(len + 1, sizeof(char));
	ft_strncpy(str + i - len, var, len);
	final = find_env_value(var, env);
	expanded = replace_variable(i, len, str, final);
	return (expanded);
}
