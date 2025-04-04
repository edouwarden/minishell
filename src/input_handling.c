#include "../include/minishell.h"
#include <unistd.h>

// Variable globale pour le dernier signal reçu
static char *g_last_signal = NULL;

void handle_sigint(int sig)
{
  (void)sig;
  g_last_signal = "\n";
  write(STDOUT_FILENO, "\n", 1); // Write newline explicitly
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}

void setup_signals(void)
{
  // Configure Ctrl+C et ignore Ctrl+"\"
  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, SIG_IGN);
}

char *concat(const char *str1, const char *str2, const char *str3, const char *str4, const char *str5)
{
  // Handle NULL inputs
  str1 = str1 ? str1 : "";
  str2 = str2 ? str2 : "";
  str3 = str3 ? str3 : "";
  str4 = str4 ? str4 : "";
  str5 = str5 ? str5 : "";

  char *temp1 = ft_strjoin(str1, str2);
  if (!temp1)
    return NULL;

  char *temp2 = ft_strjoin(temp1, str3);
  ft_gc_free(temp1);
  if (!temp2)
    return NULL;

  char *temp3 = ft_strjoin(temp2, str4);
  ft_gc_free(temp2);
  if (!temp3)
    return NULL;

  char *result = ft_strjoin(temp3, str5);
  ft_gc_free(temp3);

  return result;
}

char *get_relative_path(const char *path, const char *home)
{
  // If home is not a prefix of path, return NULL or the full path
  if (strncmp(path, home, strlen(home)) != 0)
  {
    return ft_strdup(path); // or return NULL depending on your needs
  }

  // Calculate the position after the home directory
  const char *relative = path + strlen(home);

  // Skip any leading slashes
  while (*relative == '/')
  {
    relative++;
  }

  // If we're at the end, it means path == home
  if (*relative == '\0')
  {
    return ft_strdup("~");
  }

  // Construct the relative path with ~/
  char *result = ft_strjoin("~/", relative);
  return result;
}

char *read_command_line(t_env **env)
{
  char *line = NULL;
  char *home_display = NULL;
  char *prompt = NULL;
  char *result_str = NULL;
  char *cwd ;
  char *current_path;

  if (env && *env)
  {
    if ((*env)->value && *(*env)->value && *(*env)->value != '0')
    {
      result_str = "◉ ";
    }

    cwd = getcwd(NULL, 0);
    current_path = ft_strdup(cwd);
    free(cwd);//free exeption

    t_env *env_home = is_in_env(env, ft_strdup("HOME"));

    if (current_path && env_home && env_home->value)
    {
      home_display = get_relative_path(current_path, env_home->value);
      ft_gc_free(current_path);
    }

    if (!home_display)
    {
      home_display = ft_strdup("minishell");
    }

    if (home_display)
    {
      prompt = concat("\033[0;31m", result_str, "\e[1;32mMinishell\e[2;36m ", home_display, "\e[0m\e[1;32m>\e[0m ");
      ft_gc_free(home_display);
    }

    if (prompt)
    {
      line = readline(prompt);
      ft_gc_free(prompt);
      if (line && *line)
      {
        add_history(line);
      }
      return line;
    }
  }
  else
  {
    if (!line)
    {
      line = readline("\033[0;32mMinishell>\033[0m ");
    }

    if (line && *line)
    {
      add_history(line);
    }
    return line;
  }
  return NULL;
}

void handle_eof(char *line)
{
  // Gère Ctrl+D (EOF)
  if (!line)
  {
    printf("exit\n");
    ft_gc_cleanup();
    exit(0);
  }
}
