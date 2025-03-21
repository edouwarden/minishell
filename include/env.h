/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:18:57 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/21 13:49:56 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int		get_c(char **v);
void	ft_unset(char **v, t_env **env);
t_env	*is_in_env(t_env **env, char *name);
void	ft_export(char **v, t_env **env);
void	ft_strncpy(char *src, char *dest, int n);

void	print_env(t_env **lst);
char	*get_n(char *env);
char	*get_v(char *env);
t_env	*ft_lstlast(t_env *env);
t_env	**create_env(void);
char	*dollex(char *str, t_env **env);
t_env	*new_env(char *n, char *v);
void	add_back_env(t_env *new_env, t_env **lst);
int		echo(char **arg);
int		cd(char **path, t_env **env);
int		pwd(void);
void	update_last_value(t_env **env, int value);

#endif
