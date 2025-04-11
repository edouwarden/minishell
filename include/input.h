/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:06:47 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 18:43:18 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INPUT_H
# define INPUT_H

char	*read_command_line(t_env **env);
void	handle_eof(char *line, t_env **env);

void	handle_sigint(int sig);
void	segfault_handler(int sig);
void	setup_signals(void);

char	*concat(const char **strs, int count);
char	*get_relative_path(const char *path, const char *home);

#endif
