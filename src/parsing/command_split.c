#include "../../include/minishell.h"

static char	**split_args(char *cmd, int start, int end)
{
	char	**args;
	char	*current_arg;
	int		current_pos;
	int		arg_count;
	int		arg_start;
	char	current_quote;

	// Allocation du tableau d'arguments (taille maximale: tous les caractères sont des arguments)
	args = ft_calloc(end - start + 1, sizeof(char *));
	if (!args)
		return (NULL);

	current_pos = start;
	arg_count = 0;
	while (current_pos < end)
	{
		// Ignore les espaces entre les arguments
		while (current_pos < end && cmd[current_pos] == ' ')
			current_pos++;
		if (current_pos >= end)
			break;

		// Marque le début de l'argument actuel
		arg_start = current_pos;
		
		// Gestion des quotes (simples et doubles)
		current_quote = 0;
		while (current_pos < end && (current_quote || cmd[current_pos] != ' '))
		{
			// Si on trouve une quote et qu'on n'est pas déjà dans des quotes
			if (!current_quote && (cmd[current_pos] == '"' || cmd[current_pos] == '\''))
				current_quote = cmd[current_pos];
			// Si on trouve la quote fermante correspondante
			else if (current_quote && cmd[current_pos] == current_quote)
				current_quote = 0;
			current_pos++;
		}
		if (current_quote){
			printf("Error");
			exit(1);
			//TODO: better
		}
		if (current_pos > arg_start)
		{
			// Allocation et copie de l'argument sans les quotes
			current_arg = ft_calloc(current_pos - arg_start + 1, sizeof(char));
			if (!current_arg)
			{
				free_array(args);
				return (NULL);
			}

			// Copie caractère par caractère en ignorant les quotes
			int dest_pos = 0;
			int src_pos = arg_start;
			current_quote = 0;
			while (src_pos < current_pos)
			{
				if (!current_quote && (cmd[src_pos] == '"' || cmd[src_pos] == '\''))
					current_quote = cmd[src_pos];
				else if (current_quote && cmd[src_pos] == current_quote)
					current_quote = 0;
				else
					current_arg[dest_pos++] = cmd[src_pos];
				src_pos++;
			}
			current_arg[dest_pos] = '\0';
			args[arg_count++] = current_arg;
		}
	}
	args[arg_count] = NULL;  // Marque la fin du tableau d'arguments
	return (args);
}

t_command	*create_command(char **args)
{
	t_command	*new_command;

	// Création d'une nouvelle structure de commande
	new_command = ft_calloc(1, sizeof(t_command));
	if (!new_command)
		return (NULL);

	// Initialisation des champs de la commande
	new_command->args = args;
	new_command->pipe_read = -1;      // -1 signifie pas de redirection d'entrée
	new_command->pipe_write = -1;     // -1 signifie pas de redirection de sortie
	new_command->input_fd = STDIN;    // Entrée standard par défaut
	new_command->output_fd = STDOUT;  // Sortie standard par défaut

	return (new_command);
}

t_pipeline	*split_command(char *cmd)
{
	t_pipeline	*pipeline;
	char		**current_args;
	int			current_pos;
	int			cmd_start;
	int			cmd_count;

	// Création de la structure pipeline
	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);

	// Compte le nombre de commandes (nombre de pipes + 1)
	// Ex: "cmd1 | cmd2 | cmd3" -> 2 pipes = 3 commandes
	cmd_count = 1;
	current_pos = 0;
	while (cmd[current_pos])
	{
		if (cmd[current_pos] == '|')
			cmd_count++;
		current_pos++;
	}

	// Allocation du tableau de commandes
	pipeline->commands = ft_calloc(cmd_count + 1, sizeof(t_command *));
	pipeline->cmd_count = cmd_count;
	if (!pipeline->commands)
	{
		free(pipeline);
		return (NULL);
	}

	// Parse chaque commande entre les pipes
	current_pos = 0;
	cmd_start = 0;
	cmd_count = 0;
	while (cmd[current_pos])
	{
		// Quand on trouve un pipe ou la fin de la chaîne
		if (cmd[current_pos] == '|' || cmd[current_pos + 1] == '\0')
		{
			// Parse les arguments de la commande actuelle
			current_args = split_args(cmd, cmd_start, 
				cmd[current_pos + 1] == '\0' ? current_pos + 1 : current_pos);
			
			if (!current_args)
			{
				free_pipeline(pipeline);
				return (NULL);
			}

			// Crée la structure de commande avec ses arguments
			pipeline->commands[cmd_count] = create_command(current_args);
			if (!pipeline->commands[cmd_count])
			{
				free_array(current_args);
				free_pipeline(pipeline);
				return (NULL);
			}

			cmd_count++;
			cmd_start = current_pos + 1;
		}
		current_pos++;
	}
	pipeline->commands[cmd_count] = NULL;  // Marque la fin du tableau de commandes
	return (pipeline);
} 