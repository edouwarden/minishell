/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:59:18 by enormand          #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_str_list(char **str)
{
	int	i;

	if (!DEBUG)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		printf("\033[0;33mdebug: Liste-%d: %s\033[0m\n", i + 1, str[i]);
		i++;
	}
}

static void	debug_process_format(const char **format, va_list args)
{
	char	*s;

	(*format)++;
	if (**format == 's')
	{
		s = va_arg(args, char *);
		if (!s)
			printf("%s", "(null)");
		else
			printf("%s", s);
	}
	else if (**format == 'd')
		printf("%d", va_arg(args, int));
	else if (**format == 'c')
		printf("%c", va_arg(args, int));
	else if (**format == '%')
		printf("%%");
	(*format)++;
}

void	debug_printf(const char *format, ...)
{
	va_list	args;

	if (!DEBUG)
		return ;
	printf("\033[0;33mdebug: ");
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			debug_process_format(&format, args);
		else
			putchar(*format++);
	}
	va_end(args);
	printf("\033[0m\n");
}
