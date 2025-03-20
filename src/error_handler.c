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
	// Libère chaque chaîne puis le tableau
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_commands(t_command **commands, int count)
{
	int	i;

	if (!commands)
		return ;
	// Libère chaque commande et ses ressources
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
		free(commands[i]);
		i++;
	}
	free(commands);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	// Libère le pipeline et ses ressources
	if (pipeline->commands)
		free_commands(pipeline->commands, pipeline->cmd_count);
	if (pipeline->pipe_fds)
		free(pipeline->pipe_fds);
	free(pipeline);
}

void	handle_memory_error(void)
{
	// Erreur d'allocation mémoire fatale
	ft_putstr_fd("minishell: memory allocation error\n", STDERR);
	exit(EXIT_FAILURE);
}

void	handle_command_error(char *cmd)
{
	// Affiche erreur commande non trouvée
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": command not found\n", STDERR);
} 