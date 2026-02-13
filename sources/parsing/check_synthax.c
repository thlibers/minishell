/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:24:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/10 15:58:58 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	check_quote(t_tok *tok)
{
	int	quote;
	int	i;

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

bool	check_ope(t_tok *tok)
{
	while (tok)
	{
		if (tok->type != T_WORD)
		{
			if (tok->type == T_HERE_DOC && !tok->next)
			{
				ft_fprintf(2, "\033[31mminishell: heredoc error\033[0m\n");
				return (false);
			}
			else if ((!tok->next || tok->next->type != T_WORD) || (!tok->prev && tok->type == T_PIPE))
			{
				ft_fprintf(2, "\033[31mminishell: syntax error\033[0m\n");
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
// CAS SPECIAUX :
// REDIRECTION (<, >, >>, <<),
//	on peux lui donner uniquement le fichier et il va O_CREATE + O_TRUNC le fichier (<, >)
