/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:24:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/13 16:06:16 by thlibers         ###   ########.fr       */
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
				ft_fprintf(2, EQUOTE);
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
				return (ft_fprintf(2, ESYNTAX), false);
			else if (tok->type != T_WORD && !tok->next)
				return (ft_fprintf(2, ESYNTAX), false);
			else if (tok->type == T_OR || tok->type == T_AND)
				return (ft_fprintf(2, EUNHANDLE), false);
		}
		tok = tok->next;
	}
	return (true);
}
