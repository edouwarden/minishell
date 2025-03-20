/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:01:34 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/20 17:52:25 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

void    add_to_bis(t_env **env, char *n ,char *v)
{
    t_env   *tmp;

    tmp = new_env(n, v);
    if (!tmp)
    {   
        printf("export: Memory allocation failed to add : `%s=%s'", n, v);
        return ;
    }   
    add_back_env(tmp, env);
}

void set_to_old_pwd(t_env **env, t_env *pwd, int old)
{
	char *ptr;

	if (old)
	{
		ptr = ft_calloc(7, sizeof(char));
		ptr[0] = 'O';
		ptr[1] = 'L';
		ptr[2] = 'D';
		ptr[3] = 'P';
		ptr[4] = 'W';
		ptr[5] = 'D';
		add_to_bis(env, ptr, ft_strdup(pwd->value));
	}
	else 
	{
		ptr = ft_calloc(4, sizeof(char));
		ptr[0] = 'P';
		ptr[1] = 'W';
		ptr[2] = 'D';
		add_to_bis(env, ptr, getcwd(ptr, 0));
	}
	return ;
}

void update_env(t_env **env, t_env *old_pwd, t_env *pwd)
{
	if (!old_pwd && !pwd)
		return;
	else if (pwd && old_pwd)
	{
		old_pwd->value = pwd->value;
		return ;
	}
	else if (pwd && !old_pwd)
		return(set_to_old_pwd(env, pwd, 1));
	else if (!pwd && old_pwd)
		return(set_to_old_pwd(env, NULL, 0));
}

int go_to_path(char *path, t_env **env)
{
	int error;
	t_env *ptr;
	t_env *ptr_old;

	error = chdir(path);
	if (error == -1)
	{
		perror("cd");
		return(1);
	}
	ptr_old = is_in_env(env, "OLDPWD");
	ptr = is_in_env(env, "PWD");
	update_env(env, ptr_old, ptr);
	return(0);
}

int return_to_lobby(t_env **env)
{
	//char * path;

	//path = getenv("HOME");
	return(go_to_path("~", env));
}

int cd(char **path, t_env **env)
{
	int	error;
	t_env *ptr;

	error = get_c(path);
	if (error > 2)
	{
		 printf("cd: too many arguments\n");
		 return (1);
	}
	if (!path[1])
	{
		ptr = is_in_env(env, "HOME");
		go_to_path(ptr->name, env);
	}
	if (path[1][0] == '~' || path[1][1] == '\0')
	{
		ptr = is_in_env(env, "HOME");
		if (!ptr)
			error = return_to_lobby(env);
		else
			go_to_path(ptr->name, env);
	}
	else
		error = go_to_path(path[1], env);
	return (error);
}
