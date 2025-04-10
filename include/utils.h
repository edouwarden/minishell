/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:00:00 by enormand          #+#    #+#             */
/*   Updated: 2024/04/10 10:00:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# ifndef DEBUG
#  define DEBUG 0
# endif

// Error handling functions
void	print_memory_error(void);
void	print_command_error(char *cmd);
void	print_parse_error(char *c);
void	print_exit_error(char *arg);
void	print_newline_error(void);
void	print_non_numeric_arg_error(char *arg);
void	print_too_many_args_error(void);
void	print_permission_errors(char *str);
void	print_segfault_error(int raison);
void	print_not_found_errors(char *file);
void	print_open_error(char *file, int error_code);

// Debug functions
void	debug_str_list(char **str);
void	debug_printf(const char *format, ...);

#endif