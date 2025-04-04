/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:30:35 by jsarter           #+#    #+#             */
/*   Updated: 2025/03/20 16:20:11 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include "../../include/minishell.h"

int pwd(void)
{
  char *ptr;
  char *cwd;

  ptr = NULL;
  cwd = getcwd(NULL, 0);
  ptr = ft_strdup(cwd);
  free(cwd);//free exeption
  if (!ptr)
  {
    perror("pwd");
    return (1);
  }
  printf("%s\n", ptr);
  ft_gc_free(ptr);
  return (0);
}
/*
int	main(void)
{
  pwd();
  return(0);
}
*/
