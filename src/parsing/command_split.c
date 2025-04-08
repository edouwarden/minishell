/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:07:21 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 11:07:22 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**split_args(char *cmd, int start, int end)
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
}

t_command	*create_command(char **args)
{
	t_command	*new_command;

	new_command = ft_calloc(1, sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->args = args;
	new_command->pipe_read = -1;
	new_command->pipe_write = -1;
	new_command->input_fd = STDIN;
	new_command->output_fd = STDOUT;
	new_command->input_file = NULL;
	new_command->output_file = NULL;
	new_command->heredoc_delim = NULL;
	new_command->append_mode = 0;
	return (new_command);
}

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
		handle_newline_error();
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
		handle_parse_error(error_str);
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

static char	**process_redirections(t_command *cmd, char **args)
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

t_pipeline	*split_command(char *cmd)
{
	t_pipeline	*pipeline;
	char		**current_args;
	int			current_pos;
	int			cmd_start;
	int			cmd_count;
	int			current_quote;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	cmd_count = 1;
	current_pos = 0;
	current_quote = 0;
	while (cmd[current_pos])
	{
		if (cmd[current_pos] == '|' && !current_quote)
			cmd_count++;
		if (cmd[current_pos] == '\'' || cmd[current_pos] == '"')
		{
			debug_printf("Quote found: %c", cmd[current_pos]);
			if (current_quote == cmd[current_pos])
				current_quote = 0;
			else
				current_quote = cmd[current_pos];
		}
		current_pos++;
	}
	pipeline->commands = ft_calloc(cmd_count + 1, sizeof(t_command *));
	pipeline->cmd_count = cmd_count;
	if (!pipeline->commands)
	{
		ft_gc_free(pipeline);
		return (NULL);
	}
	current_pos = 0;
	cmd_start = 0;
	cmd_count = 0;
	current_quote = 0;
	while (cmd[current_pos])
	{
		if ((cmd[current_pos] == '|' && !current_quote) || cmd[current_pos
			+ 1] == '\0')
		{
			current_args = split_args(cmd, cmd_start, cmd[current_pos
					+ 1] == '\0' ? current_pos + 1 : current_pos);
			/* Debug*/
			debug_str_list(current_args);
			if (!current_args || !*current_args)
			{
				free_pipeline(pipeline);
				return (NULL);
			}
			pipeline->commands[cmd_count] = create_command(current_args);
			if (!pipeline->commands[cmd_count])
			{
				free_array(current_args);
				free_pipeline(pipeline);
				return (NULL);
			}
			pipeline->commands[cmd_count]->args = process_redirections(pipeline->commands[cmd_count],
					current_args);
			if (!pipeline->commands[cmd_count]->args)
			{
				free_pipeline(pipeline);
				return (NULL);
			}
			cmd_count++;
			cmd_start = current_pos + 1;
		}
		if (cmd[current_pos] == '\'' || cmd[current_pos] == '"')
		{
			debug_printf("Quote found: %c", cmd[current_pos]);
			if (current_quote == cmd[current_pos])
				current_quote = 0;
			else
				current_quote = cmd[current_pos];
		}
		current_pos++;
	}
	pipeline->commands[cmd_count] = NULL;
	return (pipeline);
}
