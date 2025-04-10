/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:46:28 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 14:17:08 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	handle_redirection_symbols(char *cmd, int *current_pos,
		char current_quote)
{
	if (!current_quote && (cmd[*current_pos] == '<' || cmd[*current_pos] == '>')
		&& cmd[*current_pos + 1] != '<' && cmd[*current_pos + 1] != '>')
	{
		(*current_pos)++;
		return (1);
	}
	return (0);
}

static char	*extract_arg(char *cmd, int arg_start, int current_pos)
{
	char	*current_arg;
	int		dest_pos;
	int		src_pos;
	char	current_quote;

	current_arg = ft_calloc(current_pos - arg_start + 1, sizeof(char));
	if (!current_arg)
		return (NULL);
	dest_pos = 0;
	src_pos = arg_start;
	current_quote = 0;
	while (src_pos < current_pos)
	{
		if ((cmd[src_pos] == '"' || cmd[src_pos] == '\'') && !current_quote)
			current_quote = cmd[src_pos];
		else if (cmd[src_pos] == current_quote)
			current_quote = 0;
		else
			current_arg[dest_pos++] = cmd[src_pos];
		src_pos++;
	}
	current_arg[dest_pos] = '\0';
	return (current_arg);
}

static int	process_arg(char *cmd, int *current_pos, char ***args,
		int *arg_count)
{
	int		arg_start;
	char	current_quote;

	arg_start = *current_pos;
	current_quote = 0;
	while (*current_pos < (int)ft_strlen(cmd) && (current_quote
			|| cmd[*current_pos] != ' '))
	{
		handle_quotes(cmd[*current_pos], &current_quote);
		if (handle_redirection_symbols(cmd, current_pos, current_quote))
			break ;
		(*current_pos)++;
	}
	if (current_quote)
	{
		printf("\033[0;33m⚠️  Quote not closed\033[0m\n");
		return (0);
	}
	if (*current_pos > arg_start)
	{
		(*args)[*arg_count] = extract_arg(cmd, arg_start, *current_pos);
		if (!(*args)[(*arg_count)++])
			return (0);
	}
	return (1);
}

char	**split_args(char *cmd, int start, int end)
{
	char	**args;
	int		current_pos;
	int		arg_count;

	args = ft_calloc(end - start + 1, sizeof(char *));
	if (!args)
		return (NULL);
	current_pos = start;
	arg_count = 0;
	while (current_pos < end)
	{
		while (current_pos < end && cmd[current_pos] == ' ')
			current_pos++;
		if (current_pos >= end)
			break ;
		if (!process_arg(cmd, &current_pos, &args, &arg_count))
		{
			free_array(args);
			return (NULL);
		}
	}
	args[arg_count] = NULL;
	return (args);
}
/*char	**split_args(char *cmd, int start, int end)
{
	char	**args;
	char	*current_arg;
	int		current_pos;
	int		arg_count;
	int		arg_start;
	char	current_quote;
	int		dest_pos;
	int		src_pos;

	args = ft_calloc(end - start + 1, sizeof(char *));
	if (!args)
		return (NULL);
	current_pos = start;
	arg_count = 0;
	while (current_pos < end)
	{
		while (current_pos < end && cmd[current_pos] == ' ')
			current_pos++;
		if (current_pos >= end)
			break ;
		arg_start = current_pos;
		current_quote = 0;
		while (current_pos < end && (current_quote || cmd[current_pos] != ' '))
		{
			if ((cmd[current_pos] == '"' || cmd[current_pos] == '\'')
					&& !current_quote)
				current_quote = cmd[current_pos];
			else if (cmd[current_pos] == current_quote)
				current_quote = 0;
			if (!current_quote && (cmd[current_pos] == '<'
					|| cmd[current_pos] == '>') && cmd[current_pos + 1] != '<'
				&& cmd[current_pos + 1] != '>')
			{
				current_pos++;
				break ;
			}
			current_pos++;
			if (!current_quote && (cmd[current_pos] == '<'
					|| cmd[current_pos] == '>') && cmd[current_pos - 1] != '<'
				&& cmd[current_pos - 1] != '>')
				break ;
		}
		if (current_quote)
		{
			printf("\033[0;33m⚠️  Quote not closed\033[0m\n");
			free_array(args);
			return (NULL);
		}
		if (current_pos > arg_start)
		{
			current_arg = ft_calloc(current_pos - arg_start + 1, sizeof(char));
			if (!current_arg)
			{
				free_array(args);
				return (NULL);
			}
			dest_pos = 0;
			src_pos = arg_start;
			current_quote = 0;
			while (src_pos < current_pos)
			{
				if ((cmd[src_pos] == '"' || cmd[src_pos] == '\'')
						&& !current_quote)
					current_quote = cmd[src_pos];
				else if (cmd[src_pos] == current_quote)
					current_quote = 0;
				else
					current_arg[dest_pos++] = cmd[src_pos];
				src_pos++;
			}
			current_arg[dest_pos] = '\0';
			args[arg_count++] = current_arg;
		}
	}
	args[arg_count] = NULL;
	return (args);
}*/
