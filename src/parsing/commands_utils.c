/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:26:40 by enormand          #+#    #+#             */
/*   Updated: 2025/04/08 13:40:50 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_quotes(char current_char, char *current_quote)
{
  if (current_char == '\'' || current_char == '"')
  {
    debug_printf("Quote found: %c", current_char);
    if (*current_quote == current_char)
      *current_quote = 0;
    else if (*current_quote == 0)
      *current_quote = current_char;
  }
}

t_command *create_command(char **args)
{
  t_command *new_command;

  new_command = ft_calloc(1, sizeof(t_command));
  if (!new_command)
    return (NULL);
  new_command->args = args;
  new_command->pipe_read = -1;
  new_command->pipe_write = -1;
  new_command->input_fd = STDIN;
  new_command->output_fd = STDOUT;
  new_command->input_file = NULL;
  new_command->output_file = NULL;
  new_command->heredoc_delim = NULL;
  new_command->append_mode = 0;
  return (new_command);
}

int count_pipes(char *cmd)
{
  int count;
  int pos;
  int quote;

  count = 1;
  pos = 0;
  quote = 0;
  while (cmd[pos])
  {
    if (cmd[pos] == '|' && !quote)
      count++;
    if (cmd[pos] == '\'' || cmd[pos] == '"')
    {
      debug_printf("Quote found: %c", cmd[pos]);
      if (quote == cmd[pos])
        quote = 0;
      else
        quote = cmd[pos];
    }
    pos++;
  }
  return (count);
}
