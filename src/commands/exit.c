#include "../../include/minishell.h"

int ft_isnum(char *str)
{
  if (!str || !(*str))
    return (0);
  if ((*str < '0' || *str > '9') && *str !='-' && *str != '+')
    return (0);
  ++str;
  while (*str)
  {
      if (*str < '0' || *str > '9')
          return (0);
      str++;
  }
  return (1);
}

long long get_exit_status(char **args)
{
  long long status;

  status = 0;
  if (!args || !args[1])
    return (0);

  if (args[2] && *args[2])
  {
    printf("test\n");
    handle_too_many_args_error();
    return (1);
  }
  if (!ft_isnum(args[1]))
  {
    handle_non_numeric_arg_error(args[1]);
    return (2);
  }
  //TODO: DOMMED BY JUJU
  //is_overflow(args[1])
  status = ft_atoi(args[1]);
  if (status < 0)
    return (156);
  printf("%lld\n", status);
  if (status >=0 && status > 9223372036854775807)
  {
    handle_exit_error(args[1]);
    return (255);
  }
  // END OF DOMMED
  return (status);
}
