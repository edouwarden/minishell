/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:18:57 by jsarter           #+#    #+#             */
/*   Updated: 2025/04/11 17:45:03 by jsarter          ###   ########.fr       */
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

void				add_env_pair(t_env **env, char *n, char *v);
int					count_strings(char **v);
int					builtin_unset(char **v, t_env **env);
t_env				*is_in_env(t_env **env, char *name);
int					builtin_export(char **v, t_env **env);
void				ft_strncpy(char *src, char *dest, int n);

int					builtin_env(char **argv, t_env **lst);
char				*get_env_name(char *env);
char				*get_env_value(char *env);
t_env				*ft_lstlast(t_env *env);
t_env				**create_env(void);
char				*expand_variables(char *str, t_env **env);
t_env				*new_env(char *n, char *v);
void				add_back_env(t_env *new_env, t_env **lst);
int					builtin_echo(char **arg);
int					builtin_cd(char **path, t_env **env);
int					builtin_pwd(void);
void				set_last_result(t_env **env, long int value);
char				**convert_env_to_array(t_env **env);
void				free_array_env(char **array);
void				add_front_env(t_env *node, t_env **list);
t_env				*new_env(char *n, char *v);
void				add_back_env(t_env *new_env, t_env **lst);
char				*expand_variable(char *str, int i, t_env **env);
char				*find_env_value(char *var, t_env **env);
int					is_var_char(char c);
char				*replace_variable(int i, int len_name, char *str, char *value);
t_env				**env_backup(t_env **env);
int					builtin_exit(char **args, t_env **env);
char				*set_shell_pid(char *pid_str);

#endif
