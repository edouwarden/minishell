/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 11:06:48 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

static char	*g_last_signal = NULL;

void	handle_sigint(int sig)
{
	(void)sig;
	g_last_signal = "\n";
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	segfault_handler(int sig)
{
	int	raison;

	raison = (((&sig)[2]) / 10) % 10;
	handle_segfault_error(raison);
	ft_gc_cleanup();
	exit(1);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, segfault_handler);
}

char	*concat(const char *str1, const char *str2, const char *str3,
		const char *str4, const char *str5)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*result;

	if (!str1)
		str1 = "";
	if (!str2)
		str2 = "";
	if (!str3)
		str3 = "";
	if (!str4)
		str4 = "";
	if (!str5)
		str5 = "";
	temp1 = ft_strjoin(str1, str2);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, str3);
	ft_gc_free(temp1);
	if (!temp2)
		return (NULL);
	temp3 = ft_strjoin(temp2, str4);
	ft_gc_free(temp2);
	if (!temp3)
		return (NULL);
	result = ft_strjoin(temp3, str5);
	ft_gc_free(temp3);
	return (result);
}

char	*get_relative_path(const char *path, const char *home)
{
	const char	*relative = path + ft_strlen(home);
	char		*result;

	if (ft_strncmp(path, home, ft_strlen(home)) != 0)
	{
		return (ft_strdup(path));
	}
	while (*relative == '/')
	{
		relative++;
	}
	if (*relative == '\0')
	{
		return (ft_strdup("~"));
	}
	result = ft_strjoin("~/", relative);
	return (result);
}

char	*read_command_line(t_env **env)
{
	char	*line;
	char	*home_display;
	char	*prompt;
	char	*result_str;
	char	*cwd;
	char	*current_path;
	t_env	*env_home;

	line = NULL;
	home_display = NULL;
	prompt = NULL;
	result_str = NULL;
	if (env && *env)
	{
		if ((*env)->value && *(*env)->value && *(*env)->value != '0')
		{
			result_str = "◉ ";
		}
		cwd = getcwd(NULL, 0);
		current_path = ft_strdup(cwd);
		ft_gc_normal_free(cwd);
		env_home = is_in_env(env, ft_strdup("HOME"));
		if (current_path && env_home && env_home->value)
		{
			home_display = get_relative_path(current_path, env_home->value);
			ft_gc_free(current_path);
		}
		if (!home_display)
		{
			home_display = ft_strdup("minishell");
		}
		if (home_display)
		{
			prompt = concat("\033[0;31m", result_str,
					"\e[1;32mMinishell\e[2;36m ", home_display,
					"\e[0m\e[1;32m>\e[0m ");
			ft_gc_free(home_display);
		}
		if (prompt)
		{
			line = readline(prompt);
			ft_gc_free(prompt);
			if (line && *line)
			{
				add_history(line);
			}
			return (line);
		}
	}
	else
	{
		if (!line)
		{
			line = readline("\033[0;32mMinishell>\033[0m ");
		}
		if (line && *line)
		{
			add_history(line);
		}
		return (line);
	}
	return (NULL);
}

void	handle_eof(char *line)
{
	if (!line)
	{
		printf("exit\n");
		ft_gc_cleanup();
		exit(0);
	}
}
