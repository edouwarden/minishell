/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:36:51 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 13:35:42 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	cleanup_heredoc_file(void)
{
	unlink(".heredoc_tmp");
}

int	create_heredoc_file(void)
{
	int	heredoc_fd;

	heredoc_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		perror("minishell: heredoc");
	return (heredoc_fd);
}

int	process_heredoc_input(int heredoc_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_gc_free(line);
			break ;
		}
		if (write(heredoc_fd, line, ft_strlen(line)) == -1 || write(heredoc_fd,
				"\n", 1) == -1)
		{
			perror("minishell: heredoc write");
			ft_gc_free(line);
			return (-1);
		}
		ft_gc_free(line);
	}
	return (0);
}

int	update_command_input(t_command *cmd)
{
	if (cmd->input_file)
		ft_gc_free(cmd->input_file);
	cmd->input_file = ft_strdup(".heredoc_tmp");
	if (!cmd->input_file)
	{
		perror("minishell: memory allocation failed");
		return (-1);
	}
	return (0);
}

int	handle_heredoc(t_command *cmd)
{
	int	heredoc_fd;
	int	ret;

	if (!cmd->heredoc_delim)
		return (0);
	heredoc_fd = create_heredoc_file();
	if (heredoc_fd == -1)
		return (-1);
	ret = process_heredoc_input(heredoc_fd, cmd->heredoc_delim);
	close(heredoc_fd);
	if (ret == -1)
		return (-1);
	return (update_command_input(cmd));
}
