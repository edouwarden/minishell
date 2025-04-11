/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:01:26 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	update_last_value(t_env **env, long int value)
{
	char	*str_value;

	str_value = ft_itoa(value);
	ft_gc_free((*env)->value);
	(*env)->value = str_value;
}

int	print_env(char **argv, t_env **lst)
{
	t_env	*ptr;
	int		c;

	c = get_c(argv);
	if (c != 1)
	{
		printf("env: ‘%s’: No such file or directory\n", argv[1]);
		return (127);
	}
	ptr = (*lst)->next;
	while (ptr)
	{
		if (ptr->value && ptr->name)
			printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
	return (0);
}
