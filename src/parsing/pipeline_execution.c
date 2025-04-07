/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:45:26 by enormand          #+#    #+#             */
/*   Updated: 2024/03/05 15:45:26 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_pipes(t_pipeline *pipeline)
{
	int	pipe_index;
	int	number_of_pipes;

	// Le nombre de pipes nécessaires est toujours (nombre de commandes - 1)
	// Ex: "cmd1 | cmd2 | cmd3" -> 2 pipes nécessaires
	number_of_pipes = pipeline->cmd_count - 1;
	// Chaque pipe nécessite 2 file descriptors (lecture et écriture)
	// Donc on alloue: nombre_de_pipes * 2 entiers
	pipeline->pipe_fds = ft_calloc(number_of_pipes * 2, sizeof(int));
	if (!pipeline->pipe_fds)
		handle_memory_error();
	// Création des pipes
	pipe_index = 0;
	while (pipe_index < number_of_pipes)
	{
		// Pour chaque pipe, on crée une paire de descripteurs:
		// pipe_fds[pipe_index * 2]     -> descripteur de lecture
		// pipe_fds[pipe_index * 2 + 1] -> descripteur d'écriture
		if (pipe(&pipeline->pipe_fds[pipe_index * 2]) == -1)
		{
			perror("pipe");
			free_pipeline(pipeline);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		pipe_index++;
	}
}

static void	setup_command_pipes(t_pipeline *pipeline)
{
	int	cmd_index;

	cmd_index = 0;
	debug_printf("%d", pipeline->cmd_count);
	debug_printf("%d", pipeline->commands[cmd_index]->pipe_read);
	debug_printf("%d", pipeline->commands[cmd_index]->pipe_write);
	debug_printf("%d", pipeline->pipe_fds[(cmd_index - 1) * 2]);
	debug_printf("%d", pipeline->pipe_fds[cmd_index * 2 + 1]);
	while (cmd_index < pipeline->cmd_count)
	{
		// Pour chaque commande (sauf la première), connecter son entrée
		// au pipe de sortie de la commande précédente
		if (cmd_index > 0)
			pipeline->commands[cmd_index]->pipe_read = pipeline->pipe_fds[(cmd_index
					- 1) * 2]; // Lecture depuis le pipe précédent
		// Pour chaque commande (sauf la dernière), connecter sa sortie
		// au pipe d'entrée de la commande suivante
		if (cmd_index < pipeline->cmd_count - 1)
			pipeline->commands[cmd_index]->pipe_write = pipeline->pipe_fds[cmd_index
				* 2 + 1]; // Écriture vers le pipe suivant
		cmd_index++;
	}
}

// NEW TO check========
char	**env_list_to_array(t_env *env)
{
	int		len;
	t_env	*current;
	char	**array;
	int		i;
	size_t	total_len;
	char	*str;

	len = 0;
	current = env;
	// Compter le nombre d'éléments valides
	while (current != NULL)
	{
		if (current->name != NULL && current->value != NULL)
		{
			len++;
		}
		current = current->next;
	}
	// Allouer le tableau + case NULL finale
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	// Remplir le tableau
	while (current != NULL)
	{
		if (current->name == NULL || current->value == NULL)
		{
			current = current->next;
			continue ;
		}
		// Calculer la taille nécessaire
		total_len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
		str = ft_calloc(total_len, sizeof(char *));
		if (!str)
		{
			// Libérer la mémoire en cas d'erreur
			while (i-- > 0)
				ft_gc_free(array[i]);
			ft_gc_free(array);
			return (NULL);
		}
		// Formater la chaîne
		snprintf(str, total_len, "%s=%s", current->name, current->value);
		array[i++] = str;
		current = current->next;
	}
	array[i] = NULL; // Terminaison NULL
	return (array);
}
// NEW ========

static void	execute_piped_command(t_command *cmd, t_env **envp)
{
	char	*command_path;
	char	**env;
	int		status;

	status = 0;
	// Reset signal handlers for child process
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// Handle heredoc if needed
	if (cmd->heredoc_delim && handle_heredoc(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	// Handle input redirection
	if (handle_input_redirection(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	// Handle output redirection
	if (handle_output_redirection(cmd) == -1)
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	// If the command has no arguments after redirection processing, exit
	if (!cmd->args[0])
	{
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_SUCCESS);
	}
	// Handle pipe redirections
	if (cmd->pipe_read != -1)
	{
		if (dup2(cmd->pipe_read, STDIN) == -1)
		{
			perror("dup2: pipe read redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe_read);
	}
	if (cmd->pipe_write != -1)
	{
		if (dup2(cmd->pipe_write, STDOUT) == -1)
		{
			perror("dup2: pipe write redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe_write);
	}
	// Handle file redirections
	if (cmd->input_fd != STDIN)
	{
		if (dup2(cmd->input_fd, STDIN) == -1)
		{
			perror("dup2: input file redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->output_fd != STDOUT)
	{
		if (dup2(cmd->output_fd, STDOUT) == -1)
		{
			perror("dup2: output file redirection failed");
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
		}
	}
	// Handle built-in commands
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd->args, envp);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(status);
	}
	// Handle external commands
	env = env_list_to_array(*envp);
	if (!env)
	{
		perror("Failed to create environment array");
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(EXIT_FAILURE);
	}
	// Check permissions first if it's an absolute or relative path
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			if (access(cmd->args[0], X_OK) == -1)
			{
				ft_putstr_fd("minishell: ", STDERR);
				ft_putstr_fd(cmd->args[0], STDERR);
				ft_putstr_fd(": Permission denied\n", STDERR);
				free_array(env);
				cleanup_redirections(cmd);
				ft_gc_cleanup();
				exit(126); // Permission denied exit code
			}
			command_path = ft_strdup(cmd->args[0]);
		}
		else
		{
			handle_command_error(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(127); // Command not found exit code
		}
	}
	else
	{
		command_path = find_command_path(cmd->args[0], env);
		if (!command_path)
		{
			handle_command_error(cmd->args[0]);
			free_array(env);
			cleanup_redirections(cmd);
			ft_gc_cleanup();
			exit(127); // Command not found exit code
		}
	}
	status = execve(command_path, cmd->args, env);
	if (status == -1)
	{
		perror("execve: command execution failed");
		ft_gc_free(command_path);
		free_array(env);
		cleanup_redirections(cmd);
		ft_gc_cleanup();
		exit(126); // Command invoked cannot execute
	}
}

void	execute_pipeline(t_pipeline *pipeline)
{
	int		cmd_index;
	pid_t	*child_pids;
	int		status;
	int		last_command_status;
	int		saved_stdin;
	int		saved_stdout;
			int pipe_fd;

	// Optimisation: si une seule commande built-in, pas besoin de fork
	if (pipeline->cmd_count == 1 && is_builtin(pipeline->commands[0]->args[0]))
	{
		// Handle redirections for the builtin command
		if (handle_heredoc(pipeline->commands[0]) == -1
			|| handle_input_redirection(pipeline->commands[0]) == -1
			|| handle_output_redirection(pipeline->commands[0]) == -1)
		{
			cleanup_redirections(pipeline->commands[0]);
			update_last_value(pipeline->env, 1); // TODO: set 1 as ERROR
			return ;
		}
		// Save original file descriptors
		saved_stdin = dup(STDIN);
		saved_stdout = dup(STDOUT);
		// Set up redirections
		if (pipeline->commands[0]->input_fd != STDIN)
			dup2(pipeline->commands[0]->input_fd, STDIN);
		if (pipeline->commands[0]->output_fd != STDOUT)
			dup2(pipeline->commands[0]->output_fd, STDOUT);
		// Execute the builtin
		execute_builtin(pipeline->commands[0]->args, pipeline->env);
		// Restore original file descriptors
		dup2(saved_stdin, STDIN);
		dup2(saved_stdout, STDOUT);
		close(saved_stdin);
		close(saved_stdout);
		// Cleanup
		cleanup_redirections(pipeline->commands[0]);
		// TODO: update_last_value(pipeline->env, 0);// TODO: set 1 as ERROR
		return ;
	}
	// Préparation des pipes pour la communication entre les commandes
	setup_pipes(pipeline);
	setup_command_pipes(pipeline);
	// Allocation du tableau pour stocker les PIDs des processus enfants
	child_pids = ft_calloc(pipeline->cmd_count, sizeof(pid_t));
	if (!child_pids)
		handle_memory_error();
	// Création d'un processus pour chaque commande
	cmd_index = 0;
	while (cmd_index < pipeline->cmd_count)
	{
		child_pids[cmd_index] = fork();
		if (child_pids[cmd_index] == -1)
		{
			perror("fork: Erreur lors de la création du processus");
			ft_gc_free(child_pids);
			update_last_value(pipeline->env, 1); // TODO: set 1 as ERROR
			return ;
		}
		if (child_pids[cmd_index] == 0) // Processus enfant
		{
			// Fermeture des pipes non utilisés par cette commande
			pipe_fd = 0;
			while (pipe_fd < (pipeline->cmd_count - 1) * 2)
			{
				// Ne pas fermer les descripteurs utilisés par cette commande
				if ((cmd_index > 0 && pipe_fd == (cmd_index - 1) * 2)
					||                   // Pipe de lecture
					(cmd_index < pipeline->cmd_count - 1 && pipe_fd == cmd_index
						* 2 + 1)) // Pipe d'écriture
				{
					pipe_fd++;
					continue ;
				}
				close(pipeline->pipe_fds[pipe_fd]);
				pipe_fd++;
			}
			execute_piped_command(pipeline->commands[cmd_index], pipeline->env);
			ft_gc_cleanup();
			exit(EXIT_FAILURE);
			// Ne devrait jamais être atteint si execute_piped_command réussit
		}
		// Processus parent: fermeture des pipes après chaque fork
		if (cmd_index > 0)
			close(pipeline->pipe_fds[(cmd_index - 1) * 2]);
		// Ferme le pipe de lecture précédent
		if (cmd_index < pipeline->cmd_count - 1)
			close(pipeline->pipe_fds[cmd_index * 2 + 1]);
		// Ferme le pipe d'écriture courant
		cmd_index++;
	}
	// Attente de la fin de toutes les commandes
	last_command_status = 0;
	cmd_index = pipeline->cmd_count - 1;
	while (cmd_index >= 0)
	{
		waitpid(child_pids[cmd_index], &status, 0);
		if (cmd_index == pipeline->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_command_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_command_status = 128 + WTERMSIG(status);
			update_last_value(pipeline->env, last_command_status);
		}
		cmd_index--;
	}
	ft_gc_free(child_pids);
	update_last_value(pipeline->env, last_command_status);
		// TODO: set 1 as ERROR
	return ;
}
