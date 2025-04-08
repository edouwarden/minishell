/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:37:37 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 12:43:25 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_redirection(t_command *cmd)
{
	if (!cmd->input_file)
		return (0);
	if (cmd->input_fd != STDIN)
		close(cmd->input_fd);
	cmd->input_fd = open(cmd->input_file, O_RDONLY);
	if (cmd->input_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->input_file, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (-1);
	}
	if (cmd->input_file && ft_strcmp(cmd->input_file, ".heredoc_tmp") == 0)
		cleanup_heredoc_file();
	return (0);
}
