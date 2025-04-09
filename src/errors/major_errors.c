/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:50:55 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 10:29:38 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_memory_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: memory allocation error\033[0m\n",
		STDERR);
	ft_gc_cleanup();
	exit(EXIT_FAILURE);
}

void	print_command_error(char *cmd)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": command not found\033[0m\n", STDERR);
}

void	print_file_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: file error\033[0m\n", STDERR);
}

void	print_segfault_error(int raison)
{
	printf("\nSegmentation fault (SIGSEGV) reçu !\n");
	if (raison == 0)
		printf("\n🚀 L'astronaute 👨‍🚀 a casser sa pipe 🌕 !\n");
	else if (raison == 2)
		printf("\n🚀 L'astronaute 👨‍🚀 a oublié son casque dans l'espace 🪐 !\n");
	else if (raison == 3)
		printf("\n🚀 L'astronaute 👨‍🚀 a été aspiré par un trou noir ⚫ !\n");
	else if (raison == 4)
		printf("\n🚀 L'astronaute 👨‍🚀 a perdu le contact avec la Terre 🌍 !\n");
	else if (raison == 5)
		printf("\n🚀 L'astronaute 👨‍🚀 a rencontré des extraterrestres 👽 !\n");
	else if (raison == 6)
		printf("\n🚀 L'astronaute 👨‍🚀 a manqué d'oxygène 💨 !\n");
	else if (raison == 7)
		printf("\n🚀 L'astronaute 👨‍🚀 a été percuté par un astéroïde ☄️ !\n");
	else if (raison == 8)
		printf("\n🚀 L'astronaute 👨‍🚀 a fait une mauvaise manœuvre 🕹️ !\n");
	else if (raison == 9)
		printf("\n🚀 L'astronaute 👨‍🚀 a été gelé ❄️ dans l'espace !\n");
	else if (raison == 1)
		printf("\n🚀 L'astronaute 👨‍🚀 est mort 💀 d'une mort mystérieuse !\n");
	else
		printf("\n🚀 L'astronaute 👨‍🚀 est mort 💀 pour une raison inconnue !\n");
}
