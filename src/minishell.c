#include "inc/minishell.h"

int main(void)
{
  int status = 0;
  while (1)
  {
    status = prompt();
    if (status == 1)
      break ;
  }
  return (0);
}
