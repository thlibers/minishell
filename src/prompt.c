#include "inc/minishell.h"

int prompt(void)
{
  char *line = readline("> ");
  printf("%s\n", line);
  free(line);
  return (1);
}
