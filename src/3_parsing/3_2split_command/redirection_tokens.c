/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:02 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection_token(t_command *cmd, char *next_arg)
{
	if (cmd->input_file)
		ft_gc_free(cmd->input_file);
	cmd->input_file = ft_strdup(next_arg);
	return (0);
}

static int	handle_output_redirection_token(t_command *cmd, char *next_arg)
{
	if (cmd->output_file)
		ft_gc_free(cmd->output_file);
	cmd->output_file = ft_strdup(next_arg);
	cmd->append_mode = 0;
	return (0);
}

static int	handle_heredoc_token(t_command *cmd, char *next_arg)
{
	if (cmd->heredoc_delim)
		ft_gc_free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup(next_arg);
	return (0);
}

static int	handle_append_token(t_command *cmd, char *next_arg)
{
	if (cmd->output_file)
		ft_gc_free(cmd->output_file);
	cmd->output_file = ft_strdup(next_arg);
	cmd->append_mode = 1;
	return (0);
}

int	handle_redirection_token(t_command *cmd, char **args, int *i)
{
	char	*token;
	char	*next_arg;

	token = args[*i];
	next_arg = args[*i + 1];
	if (ft_strcmp(token, REDIR_IN) == 0)
		return (handle_input_redirection_token(cmd, next_arg));
	else if (ft_strcmp(token, REDIR_OUT) == 0)
		return (handle_output_redirection_token(cmd, next_arg));
	else if (ft_strcmp(token, REDIR_HEREDOC) == 0)
		return (handle_heredoc_token(cmd, next_arg));
	else if (ft_strcmp(token, REDIR_APPEND) == 0)
		return (handle_append_token(cmd, next_arg));
	else
		return (handle_redirection_error(token, next_arg));
}
