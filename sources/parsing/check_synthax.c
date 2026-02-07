/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:24:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/07 12:24:38 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// TROP OPERATEUR : "echo 'hello' | | cat -e" (redirection compte aussi)
