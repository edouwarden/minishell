#include "../include/minishell.h"

// Variable globale pour le dernier signal reçu
static char *g_last_signal = NULL;

void	handle_sigint(int sig)
{
	(void)sig;
	g_last_signal = "\n";
	// Réinitialise la ligne après Ctrl+C
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	// Configure Ctrl+C et ignore Ctrl+"\"
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_command_line(void)
{
	char	*line;

	// Lit une ligne et l'ajoute à l'historique
	line = readline("\033[0;32mMinishell>\033[0m ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_eof(char *line)
{
	// Gère Ctrl+D (EOF)
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
}
