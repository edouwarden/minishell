/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:38:03 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 12:42:34 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	handle_output_redirection(t_command *cmd)
{
	int	flags;

	if (!cmd->output_file)
		return (0);
	if (cmd->output_fd != STDOUT)
		close(cmd->output_fd);
	flags = O_WRONLY | O_CREAT;
	if (!cmd->append_mode)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	cmd->output_fd = open(cmd->output_file, flags, 0644);
	if (cmd->output_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->output_file, STDERR);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR);
		else
			ft_putstr_fd(": Error opening file\n", STDERR);
		return (-1);
	}
	return (0);
}
