#include "../include/minishell.h"

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

void	debug_printf(const char *format, ...)
{
	va_list	args;
	char	*s;
	int		d;
	int		c;

	if (!DEBUG)
		return ;
	printf("\033[0;33mdebug: ");
	// Manually handle up to 5 arguments
	va_start(args, format);
	// This is a simplified approach that only works for basic format strings
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				s = va_arg(args, char *);
				printf("%s", s ? s : "(null)");
			}
			else if (*format == 'd')
			{
				d = va_arg(args, int);
				printf("%d", d);
			}
			else if (*format == 'c')
			{
				// Note: char is promoted to int in varargs
				c = va_arg(args, int);
				printf("%c", c);
			}
			else if (*format == '%')
			{
				printf("%%");
			}
			format++;
		}
		else
		{
			putchar(*format++);
		}
	}
	va_end(args);
	printf("\033[0m\n");
}
