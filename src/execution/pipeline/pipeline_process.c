/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(pid_t *child_pids, int cmd_count, t_env **env)
{
	int	cmd_index;
	int	status;
	int	last_command_status;

	last_command_status = 0;
	cmd_index = cmd_count - 1;
	while (cmd_index >= 0)
	{
		waitpid(child_pids[cmd_index], &status, 0);
		if (cmd_index == cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_command_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_command_status = 128 + WTERMSIG(status);
			set_last_result(env, last_command_status);
		}
		cmd_index--;
	}
	ft_gc_free(child_pids);
	set_last_result(env, last_command_status);
}
