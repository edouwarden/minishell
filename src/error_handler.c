/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:30:26 by enormand          #+#    #+#             */
/*   Updated: 2024/03/05 15:30:26 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		ft_gc_free(arr[i]);
		i++;
	}
	ft_gc_free(arr);
}

void	ft_gc_free_commands(t_command **commands, int count)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (i < count && commands[i])
	{
		if (commands[i]->args)
			free_array(commands[i]->args);
		if (commands[i]->pipe_read != -1)
			close(commands[i]->pipe_read);
		if (commands[i]->pipe_write != -1)
			close(commands[i]->pipe_write);
		if (commands[i]->input_fd != STDIN)
			close(commands[i]->input_fd);
		if (commands[i]->output_fd != STDOUT)
			close(commands[i]->output_fd);
		ft_gc_free(commands[i]);
		i++;
	}
	ft_gc_free(commands);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->commands)
		ft_gc_free_commands(pipeline->commands, pipeline->cmd_count);
	if (pipeline->pipe_fds)
		ft_gc_free(pipeline->pipe_fds);
	ft_gc_free(pipeline);
}

void	handle_memory_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: memory allocation error\033[0m\n",
		STDERR);
	ft_gc_cleanup();
	exit(EXIT_FAILURE);
}

void	handle_command_error(char *cmd)
{
	ft_putstr_fd("\033[0;31m❌ minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": command not found\033[0m\n", STDERR);
}
void	handle_parse_error(char *c)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near `", STDERR);
	ft_putstr_fd(c, STDERR);
	ft_putstr_fd("'\033[0m\n", STDERR);
}
void	handle_newline_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: parse error near newline\033[0m\n",
		STDERR);
}
void	handle_file_error(void)
{
	ft_putstr_fd("\033[0;31m❌ minishell: file error\033[0m\n", STDERR);
}
void	handle_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
}

void	handle_too_many_args_error(void)
{
	ft_putstr_fd("minishell: too many arguments\n", STDERR);
}

void	handle_non_numeric_arg_error(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
}

void	handle_segfault_error(int raison)
{
	printf("\nSegmentation fault (SIGSEGV) reçu !\n");
	if (raison == 0)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a casser sa pipe 🌕 !\n");
	}
	else if (raison == 2)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a oublié son casque dans l'espace 🪐 !\n");
	}
	else if (raison == 3)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a été aspiré par un trou noir ⚫ !\n");
	}
	else if (raison == 4)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a perdu le contact avec la Terre 🌍 !\n");
	}
	else if (raison == 5)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a rencontré des extraterrestres 👽 hostiles !\n");
	}
	else if (raison == 6)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a manqué d'oxygène 💨 !\n");
	}
	else if (raison == 7)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a été percuté par un astéroïde ☄️ !\n");
	}
	else if (raison == 8)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a fait une mauvaise manœuvre 🕹️ !\n");
	}
	else if (raison == 9)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 a été gelé ❄️ dans l'espace !\n");
	}
	else if (raison == 1)
	{
		printf("\n🚀 L'astronaute 👨‍🚀 est mort 💀 d'une mort mystérieuse !\n");
	}
	else
	{
		printf("\n🚀 L'astronaute 👨‍🚀 est mort 💀 pour une raison inconnue !\n");
	}
}
