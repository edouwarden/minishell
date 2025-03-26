#include "../../include/minishell.h"

static char **split_args(char *cmd, int start, int end)
{
  char **args;
  char *current_arg;
  int current_pos;
  int arg_count;
  int arg_start;
  char current_quote;

  // TODO: remove
  int max_try =0;

  // Allocation du tableau d'arguments (taille maximale: tous les caractères sont des arguments)
  args = ft_calloc(end - start + 1, sizeof(char *));
  if (!args)
    return (NULL);

  current_pos = start;
  arg_count = 0;
  while (current_pos < end)
  {
    // Ignore les espaces entre les arguments
    while (current_pos < end && cmd[current_pos] == ' ')
      current_pos++;
    if (current_pos >= end)
      break;

    // Marque le début de l'argument actuel
    arg_start = current_pos;

    // Gestion des quotes (simples et doubles)
    current_quote = 0;
    while (current_pos < end && (current_quote || cmd[current_pos] != ' ' ))
    {
      //printf("%c",cmd[current_pos]);
      // Si on trouve une quote et qu'on n'est pas déjà dans des quotes
      if (!current_quote && (cmd[current_pos] == '"' || cmd[current_pos] == '\''))
        current_quote = cmd[current_pos];
      // Si on trouve la quote fermante correspondante
      else if (current_quote && cmd[current_pos] == current_quote)
        current_quote = 0;
      if (!current_quote && (cmd[current_pos] == '<' || cmd[current_pos] == '>') && cmd[current_pos+1] && cmd[current_pos+1] != '<' && cmd[current_pos+1] != '>') // END <*x or >*x arg
      {
        current_pos++;
        break;
      }
      current_pos++;
      if (!current_quote && cmd[current_pos] && (cmd[current_pos] == '<' || cmd[current_pos] == '>')&& cmd[current_pos-1] && cmd[current_pos-1] != '<' && cmd[current_pos-1] != '>'){ // END current args before < or >
        break;
      }

    }
    //printf("\narg: %s, start: %d, end: %d\n", cmd, arg_start,current_pos);
    if (current_quote)
    {
      printf("\033[0;33m⚠️ Quote not closed\033[0m\n");
      return (NULL);
      // TODO: better
    }
    if (current_pos > arg_start)
    {
      // Allocation et copie de l'argument sans les quotes
      current_arg = ft_calloc(current_pos - arg_start + 1, sizeof(char));
      if (!current_arg)
      {
        free_array(args);
        return (NULL);
      }

      // Copie caractère par caractère en ignorant les quotes
      int dest_pos = 0;
      int src_pos = arg_start;
      current_quote = 0;
      while (src_pos < current_pos)
      {
        if (!current_quote && (cmd[src_pos] == '"' || cmd[src_pos] == '\''))
          current_quote = cmd[src_pos];
        else if (current_quote && cmd[src_pos] == current_quote)
          current_quote = 0;
        else
          current_arg[dest_pos++] = cmd[src_pos];
        src_pos++;
      }
      current_arg[dest_pos] = '\0';
      args[arg_count++] = current_arg;
    }
    max_try++;
    if (max_try > 5)
      return (NULL);
  }
  args[arg_count] = NULL; // Marque la fin du tableau d'arguments
  return (args);
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

static void handle_redirection_token(t_command *cmd, char **args, int *i)
{
  char *token;
  char *next_arg;

  token = args[*i];
  next_arg = args[*i + 1];

  if (!next_arg)
  {
    ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR);
    return;
  }
  printf("%s",token);
  if (strcmp(token, REDIR_IN) == 0)
  {
    if (cmd->input_file)
      free(cmd->input_file);
    cmd->input_file = ft_strdup(next_arg);
  }
  else if (strcmp(token, REDIR_OUT) == 0)
  {
    if (cmd->output_file)
      free(cmd->output_file);
    cmd->output_file = ft_strdup(next_arg);
    cmd->append_mode = 0;
  }
  else if (strcmp(token, REDIR_HEREDOC) == 0)
  {
    if (cmd->heredoc_delim)
      free(cmd->heredoc_delim);
    cmd->heredoc_delim = ft_strdup(next_arg);
  }
  else if (strcmp(token, REDIR_APPEND) == 0)
  {
    if (cmd->output_file)
      free(cmd->output_file);
    cmd->output_file = ft_strdup(next_arg);
    cmd->append_mode = 1;
  }

  // Remove redirection token and its argument from args array
  free(args[*i]);
  free(args[*i + 1]);
  args[*i] = NULL;
  args[*i + 1] = NULL;
  *i += 1;
}

static char **process_redirections(t_command *cmd, char **args)
{
  char **new_args;
  int i;
  int j;
  int count;

  i = 0;
  count = 0;
  while (args[i])
  {
    if (args[i] && (strcmp(args[i], REDIR_IN) == 0 ||
                    strcmp(args[i], REDIR_OUT) == 0 ||
                    strcmp(args[i], REDIR_HEREDOC) == 0 ||
                    strcmp(args[i], REDIR_APPEND) == 0))
    {
      handle_redirection_token(cmd, args, &i);
    }
    else if (args[i])
      count++;
    i++;
  }

  new_args = ft_calloc(count + 1, sizeof(char *));
  if (!new_args)
    return (NULL);

  i = 0;
  j = 0;
  while (args[i])
  {
    if (args[i])
      new_args[j++] = args[i];
    i++;
  }
  new_args[j] = NULL;
  free(args);

  return (new_args);
}

t_pipeline *split_command(char *cmd)
{
  t_pipeline *pipeline;
  char **current_args;
  int current_pos;
  int cmd_start;
  int cmd_count;

  // Création de la structure pipeline
  pipeline = ft_calloc(1, sizeof(t_pipeline));
  if (!pipeline)
    return (NULL);

  // Compte le nombre de commandes (nombre de pipes + 1)
  // Ex: "cmd1 | cmd2 | cmd3" -> 2 pipes = 3 commandes
  cmd_count = 1;
  current_pos = 0;
  while (cmd[current_pos])
  {
    if (cmd[current_pos] == '|')
      cmd_count++;
    current_pos++;
  }

  // Allocation du tableau de commandes
  pipeline->commands = ft_calloc(cmd_count + 1, sizeof(t_command *));
  pipeline->cmd_count = cmd_count;
  if (!pipeline->commands)
  {
    free(pipeline);
    return (NULL);
  }

  // Parse chaque commande entre les pipes
  current_pos = 0;
  cmd_start = 0;
  cmd_count = 0;
  while (cmd[current_pos])
  {
    if (cmd[current_pos] == '|' || cmd[current_pos + 1] == '\0')
    {
      // Parse les arguments de la commande actuelle
      current_args = split_args(cmd, cmd_start,
                                cmd[current_pos + 1] == '\0' ? current_pos + 1 : current_pos);

      if (!current_args)
      {
        free_pipeline(pipeline);
        return (NULL);
      }
      pipeline->commands[cmd_count] = create_command(current_args);
      if (!pipeline->commands[cmd_count])
      {
        free_array(current_args);
        free_pipeline(pipeline);
        return (NULL);
      }

      // Process redirections after command creation
      pipeline->commands[cmd_count]->args =
          process_redirections(pipeline->commands[cmd_count], current_args);
      if (!pipeline->commands[cmd_count]->args)
      {
        free_pipeline(pipeline);
        return (NULL);
      }
      cmd_count++;
      cmd_start = current_pos + 1;
    }
    current_pos++;
  }
  pipeline->commands[cmd_count] = NULL;
  return (pipeline);
}
