/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:01:26 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/28 15:26:33 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

void update_last_value(t_env **env,long int value)
{
	char *str_value;

	str_value = ft_itoa(value);
	free((*env)->value);
	(*env)->value = str_value;
}

int	print_env(t_env **lst)
{
	t_env	*ptr;

	ptr = (*lst)->next;
	while (ptr)
	{
		if (ptr->value)
			printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
	return (0);
}
