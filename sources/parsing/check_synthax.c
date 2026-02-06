

#include "includes/minishell.h"

bool  check_quote(t_tok *tok)
{
  int quote;
  int i;

  while (tok)
  {
    if (tok->type == T_WORD)
    {
      i = 0;
      quote = 0;
      while (tok->str[i])
      {
        is_inquote(&quote, tok->str[i]);
        i++;
      }
      if (quote != 0)
      {
        printf("BAD QUOTES\n");
        return (false);
      }
    }
    tok = tok->next;
  }
  return (true);
}

// CAS MESSAGE ERREUR 
// QUOTE PAS FERMER
// OPERATEUR SEUL : "echo 'hello' |"
// TROP OPERATEUR : "echo 'hello' | | cat -e"
