#include "../../include/minishell.h"

static void cleanup_heredoc_file(void)
{
  unlink(".heredoc_tmp");
}

int handle_heredoc(t_command *cmd)
{
  char *line;
  int heredoc_fd;

  if (!cmd->heredoc_delim)
    return (0);

  heredoc_fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (heredoc_fd == -1)
  {
    perror("minishell: heredoc");
    return (-1);
  }

  while (1)
  {
    line = readline("> ");
    if (!line)
      break;

    if (strcmp(line, cmd->heredoc_delim) == 0)
    {
      free(line);
      break;
    }

    write(heredoc_fd, line, strlen(line));
    write(heredoc_fd, "\n", 1);
    free(line);
  }

  close(heredoc_fd);
  cmd->input_file = ft_strdup(".heredoc_tmp");
  return (0);
}

int handle_input_redirection(t_command *cmd)
{
  if (!cmd->input_file)
    return (0);

  if (cmd->input_fd != STDIN)
    close(cmd->input_fd);

  cmd->input_fd = open(cmd->input_file, O_RDONLY);
  if (cmd->input_fd == -1)
  {
    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(cmd->input_file, STDERR);
    ft_putstr_fd(": No such file or directory\n", STDERR);
    return (-1);
  }

  if (strcmp(cmd->input_file, ".heredoc_tmp") == 0)
    cleanup_heredoc_file();

  return (0);
}

int handle_output_redirection(t_command *cmd)
{
  int flags;

  if (!cmd->output_file)
    return (0);

  if (cmd->output_fd != STDOUT)
    close(cmd->output_fd);

  flags = O_WRONLY | O_CREAT;
  if (cmd->append_mode)
    flags |= O_APPEND;
  else
    flags |= O_TRUNC;

  cmd->output_fd = open(cmd->output_file, flags, 0644);
  if (cmd->output_fd == -1)
  {
    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(cmd->output_file, STDERR);
    ft_putstr_fd(": Permission denied\n", STDERR);
    return (-1);
  }

  return (0);
}

void cleanup_redirections(t_command *cmd)
{
  if (cmd->input_file)
  {
    free(cmd->input_file);
    cmd->input_file = NULL;
  }
  if (cmd->output_file)
  {
    free(cmd->output_file);
    cmd->output_file = NULL;
  }
  if (cmd->heredoc_delim)
  {
    free(cmd->heredoc_delim);
    cmd->heredoc_delim = NULL;
  }
  if (cmd->input_fd != STDIN)
  {
    close(cmd->input_fd);
    cmd->input_fd = STDIN;
  }
  if (cmd->output_fd != STDOUT)
  {
    close(cmd->output_fd);
    cmd->output_fd = STDOUT;
  }
}