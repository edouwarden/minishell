/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:01:26 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/19 15:33:24 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

void	print_env(t_env **lst)
{
	t_env	*ptr;

	ptr = *lst;
	while (ptr)
	{
		if (ptr->value)
			printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
