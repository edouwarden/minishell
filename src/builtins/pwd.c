/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:30:35 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 16:36:59 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

int	pwd(void)
{
	char	*ptr;
	char	*cwd;

	ptr = NULL;
	cwd = getcwd(NULL, 0);
	ptr = ft_strdup(cwd);
	ft_gc_normal_free(cwd);
	if (!ptr)
	{
		if (errno == 2)
		{
			printf("pwd: error retrieving current directory: \
			getcwd: cannot access \
			parent directories: No such file or directory\n");
		}
		else
			perror("pwd");
		return (1);
	}
	printf("%s\n", ptr);
	ft_gc_free(ptr);
	return (0);
}
