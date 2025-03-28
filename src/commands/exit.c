#include "../../include/minishell.h"

long long get_exit_status(char **args)
{
  long long status;

  status = 0;
  if (!args || !args[0])
    return (0);

  status = ft_atoi(args[0]);
  if (status < 0 || status > 9223372036854775807)
  {
    handle_exit_error(args[0]);
    return (255);
  }
  return (status);
}