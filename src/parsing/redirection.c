/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:02 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 10:29:38 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_redirection_token(t_command *cmd, char **args, int *i)
{
	char	*token;
	char	*next_arg;
	int		has_error;
	char	error_str[2];

	has_error = 0;
	token = args[*i];
	next_arg = args[*i + 1];
	error_str[0] = token[0];
	error_str[1] = '\0';
	if (!next_arg)
	{
		print_newline_error();
		return (1);
	}
	if (ft_strcmp(token, REDIR_IN) == 0)
	{
		if (cmd->input_file)
			ft_gc_free(cmd->input_file);
		cmd->input_file = ft_strdup(next_arg);
	}
	else if (ft_strcmp(token, REDIR_OUT) == 0)
	{
		if (cmd->output_file)
			ft_gc_free(cmd->output_file);
		cmd->output_file = ft_strdup(next_arg);
		cmd->append_mode = 0;
	}
	else if (ft_strcmp(token, REDIR_HEREDOC) == 0)
	{
		if (cmd->heredoc_delim)
			ft_gc_free(cmd->heredoc_delim);
		cmd->heredoc_delim = ft_strdup(next_arg);
	}
	else if (ft_strcmp(token, REDIR_APPEND) == 0)
	{
		if (cmd->output_file)
			ft_gc_free(cmd->output_file);
		cmd->output_file = ft_strdup(next_arg);
		cmd->append_mode = 1;
	}
	else
	{
		print_parse_error(error_str);
		return (1);
	}
	return (has_error);
}

static int	is_redirection_token(char *token)
{
	while (*token)
	{
		if (*token != '<' && *token != '>')
			return (0);
		token++;
	}
	return (1);
}

char	**process_redirections(t_command *cmd, char **args)
{
	char	**new_args;
	int		i;
	int		j;
	int		count;
	int		error;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!is_redirection_token(args[i]))
		{
			count++;
		}
		else
		{
			error = handle_redirection_token(cmd, args, &i);
			if (error)
				return (NULL);
			i++;
			continue ;
		}
		i++;
	}
	new_args = ft_calloc(count + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i] && !is_redirection_token(args[i]))
		{
			new_args[j++] = ft_strdup(args[i]);
			if (!new_args[j - 1])
			{
				while (--j >= 0)
					ft_gc_free(new_args[j]);
				ft_gc_free(new_args);
				return (NULL);
			}
		}
		else if (args[i])
		{
			i++;
		}
		i++;
	}
	new_args[j] = NULL;
	i = 0;
	while (args[i])
	{
		ft_gc_free(args[i]);
		i++;
	}
	ft_gc_free(args);
	return (new_args);
}

void	cleanup_redirections(t_command *cmd)
{
	if (cmd->input_file)
	{
		ft_gc_free(cmd->input_file);
		cmd->input_file = NULL;
	}
	if (cmd->output_file)
	{
		ft_gc_free(cmd->output_file);
		cmd->output_file = NULL;
	}
	if (cmd->heredoc_delim)
	{
		ft_gc_free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
	if (cmd->input_fd != STDIN)
	{
		close(cmd->input_fd);
		cmd->input_fd = STDIN;
	}
	if (cmd->output_fd != STDOUT)
	{
		close(cmd->output_fd);
		cmd->output_fd = STDOUT;
	}
}
