/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:01:34 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/20 11:42:51 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

int go_to_path(char *path, t_env **)
{
	int error;
	t_env *ptr;

	error = chdir(path);
	if (error == -1)
	{
		perror("cd");
		return(1);
	}
	ptr = is_in_env();

	return(0);
}

int return_to_lobby()
{
	char * path;

	path = getenv("HOME");
	return(go_to_path(path));
}

int cd(char **path, t_env **env)
{
	int	error;

	if (!path[1])
		error = return_to_lobby();
	else
		error = go_to_path(path[1]);
	return (error);
}

int main(int c, char **v)
{
	if (c > 2)
		return (0);
	if (c == 1)
		cd(NULL);
	else 
		cd(v[1]);
	pwd();
	printf();
	cd(NULL);
	pwd();
}
