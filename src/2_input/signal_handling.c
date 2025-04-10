/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 11:45:23 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/env.h"
#include "../../include/minishell.h"

static char	*g_last_signal = NULL;

void	handle_sigint(int sig)
{
	t_env	**env;

	(void)sig;
	g_last_signal = "\n";
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	env = need_env(NULL);
	update_last_value(env, 130);
}

void	segfault_handler(int sig)
{
	int	raison;

	raison = ((&sig)[6]) % 10;
	debug_printf("segfault random value: %d", raison);
	print_segfault_error(raison);
	ft_gc_cleanup();
	exit(1);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, segfault_handler);
}
