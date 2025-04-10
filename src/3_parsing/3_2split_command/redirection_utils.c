/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:02 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 10:29:38 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_redirection_error(char *token, char *next_arg)
{
	char	error_str[2];

	if (!next_arg)
	{
		print_newline_error();
		return (1);
	}
	error_str[0] = token[0];
	error_str[1] = '\0';
	print_parse_error(error_str);
	return (1);
}

int	is_redirection_token(char *token)
{
	while (*token)
	{
		if (*token != '<' && *token != '>')
			return (0);
		token++;
	}
	return (1);
}

void	cleanup_old_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_gc_free(args[i]);
		i++;
	}
	ft_gc_free(args);
}

char	**allocate_new_args(int count)
{
	char	**new_args;

	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	return (new_args);
}

int	count_non_redirection_args(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (!is_redirection_token(args[i]))
			count++;
		else
			i++;
		i++;
	}
	return (count);
}
