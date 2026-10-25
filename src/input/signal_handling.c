/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	t_env	**env;

	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	env = env_backup(NULL);
	set_last_result(env, 130);
}

void	handle_sigusr1(int sig, siginfo_t *info, void *ucontext)
{
	char	*pid_str;

	(void) sig;
	(void) ucontext;
	pid_str = ft_itoa(info->si_pid);
	set_shell_pid(pid_str);
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
	struct sigaction	sa1;

	sigemptyset(&sa1.sa_mask);
	sa1.sa_handler = NULL;
	sa1.sa_flags = SA_SIGINFO;
	sa1.sa_sigaction = handle_sigusr1;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, segfault_handler);
	sigaction(SIGUSR1, &sa1, NULL);
}
