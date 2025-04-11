/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:02 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_non_redirection_arg(char **new_args, char *arg, int *j)
{
	new_args[*j] = ft_strdup(arg);
	if (!new_args[*j])
	{
		while (--*j >= 0)
			ft_gc_free(new_args[*j]);
		ft_gc_free(new_args);
		return (1);
	}
	(*j)++;
	return (0);
}

static int	process_args(t_command *cmd, char **args, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i] && !is_redirection_token(args[i]))
		{
			if (copy_non_redirection_arg(new_args, args[i], &j))
				return (1);
		}
		else if (args[i])
		{
			if (handle_redirection_token(cmd, args, &i))
				return (1);
			i++;
		}
		i++;
	}
	new_args[j] = NULL;
	return (0);
}

char	**process_redirections(t_command *cmd, char **args)
{
	char	**new_args;
	int		count;

	count = count_non_redirection_args(args);
	new_args = allocate_new_args(count);
	if (!new_args)
		return (NULL);
	if (process_args(cmd, args, new_args))
		return (NULL);
	cleanup_old_args(args);
	return (new_args);
}
