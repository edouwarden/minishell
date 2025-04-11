/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/09 11:45:23 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/env.h"
#include "../../include/minishell.h"

static char	*create_prompt(t_env **env, const char *result_str)
{
	char	*home_display;
	char	*prompt;
	char	*cwd;
	char	*current_path;
	t_env	*env_home;

	cwd = getcwd(NULL, 0);
	current_path = ft_strdup(cwd);
	ft_gc_normal_free(cwd);
	env_home = is_in_env(env, ft_strdup("HOME"));
	if (current_path && env_home && env_home->value)
	{
		home_display = get_relative_path(current_path, env_home->value);
		ft_gc_free(current_path);
	}
	else
		home_display = ft_strdup("minishell");
	if (home_display)
	{
		prompt = concat((const char *[]){"\033[0;31m", result_str, \
"\e[1;32mMinishell\e[2;36m ", home_display, "\e[0m\e[1;32m>\e[0m "}, 5);
		ft_gc_free(home_display);
		return (prompt);
	}
	return (NULL);
}

char	*read_command_line(t_env **env)
{
	char	*line;
	char	*prompt;
	char	*result_str;

	line = NULL;
	result_str = NULL;
	if (env && *env && (*env)->value && *(*env)->value && *(*env)->value != '0')
		result_str = "◉ ";
	if (!env || !*env)
	{
		line = readline("\033[0;32mMinishell>\033[0m ");
		if (line && *line)
			add_history(line);
		return (line);
	}
	prompt = create_prompt(env, result_str);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	ft_gc_free(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	handle_eof(char *line, t_env **env)
{
	int	exit_code;

	if (!line)
	{
		exit_code = ft_atoi((*env)->value);
		printf("exit\n");
		ft_gc_cleanup();
		exit(exit_code);
	}
}
