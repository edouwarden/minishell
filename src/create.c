/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:00:33 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/26 15:15:30 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

void	add_back_env(t_env *new_env, t_env **lst)
{
	t_env	*ptr;

	if (!lst || !new_env)
	{
		*lst = new_env;
		return ;
	}
	ptr = ft_lstlast(*lst);
	if (!ptr)
	{
		*lst = new_env;
		return ;
	}
	ptr->next = new_env;
	new_env->next = NULL;
}

void	add_front_env(t_env *node, t_env **list)
{
	if (!node)
		return ;
	if (list)
		node->next = *list;
	*list = node;
}

t_env	*new_env(char *n, char *v)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!n || !v || !new_node)
	{
		if (n)
			free(n);
		if (v)
			free(v);
		if (new_node)
			free(new_node);
		return (NULL);
	}
	new_node->name = n;
	new_node->value = v;
	new_node->next = NULL;
	return (new_node);
}

void	env_clear(t_env **lst)
{
	t_env	*suiv;
	t_env	*prev;

	suiv = *lst;
	prev = *lst;
	while (suiv)
	{
		free(suiv->name);
		free(suiv->value);
		suiv = suiv->next;
		free(prev);
		prev = suiv;
	}
	free(lst);
}

void handle_shell_level(t_env **env)
{
	t_env	*lvl;
	int		tmp;

	lvl = is_in_env(env, ft_strdup("SHLVL"));
	if (!lvl)
	{
		lvl = new_env(ft_strdup("SHLVL"), ft_strdup("0"));
		add_back_env(lvl, env);
		return ;
	}
	tmp = ft_atoi(lvl->value);
	tmp ++;
	if (tmp >= 1000 || tmp < 0)
	{
		if (tmp >= 1000)
			printf(": warning: shell level (%d) too high, resetting to 1\n", tmp);
		tmp = 0;
	}
	free(lvl->value);
	lvl->value = ft_itoa(tmp);
}

t_env	**create_env(void)
{
	int		i;
	char	**envp;
	t_env	*tmp;
	t_env	**list;

	list = (t_env **)calloc(sizeof(t_env *), 1);
	if (!list)
		return (NULL);
	envp = __environ;
	tmp = new_env(get_n(envp[0]), get_v(envp[0]));
	add_back_env(tmp, list);
	i = 1;
	while (envp[i])
	{
		tmp = new_env(get_n(envp[i]), get_v(envp[i]));
		if (!tmp)
		{
			env_clear(list);
			return (NULL);
		}
		add_back_env(tmp, list);
		i++;
	}
	tmp = new_env(ft_strdup("LAST_RESULT"), ft_strdup("0"));
	add_front_env(tmp, list);
	handle_shell_level(list);
	return (list);
}

/*
int	main(int argc, char **argv)
{
	t_env	**test;
	t_env	*suiv;
	char *dollex_marex;
	int		i;

	test = create_env();
	if (!test)
		return (0);
	printf("%p\n", test);
	print_env(test);
	i = 1;
	if (argc >= 2)
	{
		while(i < argc)
		{
			if (i != 2 )
			{
				dollex_marex = dollex(argv[i], test);
				printf("avant : %s\napres : %s\n",argv[i], dollex_marex);
				argv[i] = dollex_marex;
			}
			i++;
		}
		ft_export(argv, test);
		print_env(test);
		if (argc >= 3)
			ft_unset(argv + 1, test);
		printf("\n\n  unset\n\n\n");
		print_env(test);
		i = 1;
		while(i < argc)
		{
			if (i != 2 )
			{
				free(argv[i]);
			}
			i++;
		}
		env_clear(test);
	}
	return (0);
}
*/
