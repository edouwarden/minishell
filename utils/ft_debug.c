#include "../include/minishell.h"
void debug_str_list(char **str){
  if (!DEBUG)
    return;
  int i;
  i = 0;
  while (str[i] != NULL)
    printf("\033[0;33mdebug: %s\033[0m\n", str[i++]);
}
