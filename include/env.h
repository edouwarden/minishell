/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:18:57 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/04 17:47:03 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void				add_to_bis(t_env **env, char *n, char *v);
int					get_c(char **v);
int					ft_unset(char **v, t_env **env);
t_env				*is_in_env(t_env **env, char *name);
int					ft_export(char **v, t_env **env);
void				ft_strncpy(char *src, char *dest, int n);

int					print_env(t_env **lst);
char				*get_n(char *env);
char				*get_v(char *env);
t_env				*ft_lstlast(t_env *env);
t_env				**create_env(void);
char				*dollex(char *str, t_env **env);
t_env				*new_env(char *n, char *v);
void				add_back_env(t_env *new_env, t_env **lst);
int					echo(char **arg);
int					cd(char **path, t_env **env);
int					pwd(void);
void				update_last_value(t_env **env, long int value);
char				**convert_env_to_array(t_env **env);
void				free_array_env(char **array);

#endif
