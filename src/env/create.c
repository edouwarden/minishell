/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:00:33 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/09 12:06:54 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

t_env	**env_clear(t_env **lst)
{
	t_env	*suiv;
	t_env	*prev;

	suiv = *lst;
	prev = *lst;
	while (suiv)
	{
		ft_gc_free(suiv->name);
		ft_gc_free(suiv->value);
		suiv = suiv->next;
		ft_gc_free(prev);
		prev = suiv;
	}
	ft_gc_free(lst);
	return (NULL);
}

void	handle_shell_level(t_env **env)
{
	t_env	*lvl;
	int		tmp;

	lvl = is_in_env(env, ft_strdup("SHLVL"));
	if (!lvl)
	{
		lvl = new_env(ft_strdup("SHLVL"), ft_strdup("1"));
		add_back_env(lvl, env);
		return ;
	}
	tmp = ft_atoi(lvl->value);
	tmp++;
	if (tmp >= 1000 || tmp < 0)
	{
		if (tmp >= 1000)
			printf(": warning: shell level (%d) too high, resetting to 1\n",
				tmp);
		tmp = 1;
	}
	ft_gc_free(lvl->value);
	lvl->value = ft_itoa(tmp);
}

t_env	**remember_no_env(t_env **env)
{
	t_env	*tmp;
	char	*ptr;

	ptr = ft_calloc(4, sizeof(char));
	ptr[0] = 'P';
	ptr[1] = 'W';
	ptr[2] = 'D';
	add_to_bis(env, ptr, getcwd(NULL, 0));
	tmp = new_env(ft_strdup("LAST_RESULT"), ft_strdup("0"));
	add_front_env(tmp, env);
	handle_shell_level(env);
	ptr = getcwd(NULL, 0);
	add_to_bis(env, ft_strdup("_"), ft_strjoin(ptr, "/./minishell"));
	ft_gc_normal_free(ptr);
	need_env(env);
	return (env);
}

void	some_more_changes(t_env **env)
{
	t_env	*tmp;

	tmp = new_env(ft_strdup("LAST_RESULT"), ft_strdup("0"));
	add_front_env(tmp, env);
	handle_shell_level(env);
	need_env(env);
}

t_env	**create_env(void)
{
	int		i;
	char	**envp;
	t_env	*tmp;
	t_env	**list;

	list = (t_env **)ft_calloc(1, sizeof(t_env *));
	if (!list)
		return (NULL);
	envp = __environ;
	if (!envp[0])
		return (remember_no_env(list));
	tmp = new_env(get_n(envp[0]), get_v(envp[0]));
	add_back_env(tmp, list);
	i = 1;
	while (envp[i])
	{
		tmp = new_env(get_n(envp[i]), get_v(envp[i]));
		if (!tmp)
			return (env_clear(list));
		add_back_env(tmp, list);
		i++;
	}
	some_more_changes(list);
	return (list);
}
