/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:48:38 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/28 20:49:12 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool  is_in_quote(char *str, int card_loc)
{
  bool quote;
  int i;

  quote = 0;
  i = 0;
  while (str[i] && i < card_loc)
  {
    if (str[i] == '"' && quote == false)
      quote = true;
    else if (str[i] == '"' && quote == true)
      quote = false;
    i++;
  }
  return (quote);
}

bool  expand_wildcard(t_tok **tok, int *i)
{
  if (is_in_quote((*tok)->str, *i))
  {
    
  }
}
