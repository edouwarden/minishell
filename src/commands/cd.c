/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:01:34 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/31 13:38:54 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

void    add_to_bis(t_env **env, char *n ,char *v)
{
    t_env   *tmp;

    tmp = new_env(n, v);
    if (!tmp)
        return ;
    add_back_env(tmp, env);
}

void set_to_old_pwd(t_env **env, t_env *pwd, int old)
{
	char *ptr;
  char *cwd;

	if (old)
	{
		ptr = ft_calloc(7, sizeof(char));
		if (!ptr)
			return ;
    ft_strlcpy(ptr,"OLDPWD",6);
		add_to_bis(env, ptr, ft_strdup(pwd->value));
    cwd = getcwd(NULL, 0);
		pwd->value = ft_strdup(cwd);
    free(cwd);//free exeption
	}
	else
	{
		ptr = ft_calloc(4, sizeof(char));
		if (!ptr)
			return ;
		ft_strlcpy(ptr,"PWD",3);
    cwd = getcwd(NULL, 0);
		add_to_bis(env, ptr, ft_strdup(cwd));
    free(cwd);//free exeption
	}
	return ;
}

void update_env(t_env **env, t_env *old_pwd, t_env *pwd)
{
  char *cwd;
	if ((!old_pwd && !pwd))
		return ;
	else if (pwd && old_pwd)
	{
		old_pwd->value = pwd->value;
    cwd =getcwd(NULL, 0);
		pwd->value = ft_strdup(cwd);
    free(cwd);//free exeption
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

	ptr_old = is_in_env(env, ft_strdup("OLDPWD"));
	ptr = is_in_env(env, ft_strdup("PWD"));
	error = chdir(path);
	if (error == -1)
	{
		perror("cd");
		return(1);
	}
	ptr_old = is_in_env(env, ft_strdup("OLDPWD"));
	ptr = is_in_env(env, ft_strdup("PWD"));
	update_env(env, ptr_old, ptr);
	return(0);
}

int cd(char **path, t_env **env)
{
	int	error;
	t_env *ptr;

	error = get_c(path);
	if (error > 2)
	{
		write(2, "cd: too many arguments\n",23);
		 return (1);
	}
	if (!path[1] || (path[1][0] == '~' && path[1][1] == '\0'))
	{
		ptr = is_in_env(env, ft_strdup("HOME"));
		if (ptr)
			go_to_path(ptr->value, env);
		else
			printf("cd: HOME not set\n");
	}
	/*else if (path[1][0] == '~' && path[1][1] == '\0')
	{
		ptr = is_in_env(env, ft_strdup("HOME"));
		if (!ptr)
			error = go_to_path(path[1], env);
		else
			go_to_path(ptr->value, env);
	}*/
	else
		error = go_to_path(path[1], env);
	return (error);
}
