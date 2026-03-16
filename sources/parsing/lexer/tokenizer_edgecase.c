/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_edgecase.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:09:12 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/16 14:19:01 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_tok	*setup(t_tok **tok, t_tok *head, t_tok *prev)
{
	t_tok	*cmd;
	t_tok	*save;
	t_tok	*last_arg;
	t_tok	*next_ope;

	cmd = *tok;
	save = cmd->prev;
	while ((*tok)->next && (*tok)->next->type == T_WORD)
		*tok = (*tok)->next;
	last_arg = *tok;
	next_ope = (*tok)->next;
	head->prev = last_arg;
	last_arg->next = head;
	cmd->prev = prev;
	if (prev)
		prev->next = cmd;
	save->next = next_ope;
	if (next_ope)
		next_ope->prev = save;
	*tok = cmd;
	while (head->prev)
		head = head->prev;
	return (head);
}

t_tok	*back_tofirst(t_tok **tok)
{
	t_tok	*head;
	t_tok	*previous;

	head = *tok;
	previous = (*tok)->prev;
	while (*tok && (*tok)->next && ((*tok)->type >= T_HERE_DOC
			|| ((*tok)->type == T_WORD && (*tok)->prev->type >= T_HERE_DOC)))
		*tok = (*tok)->next;
	if ((*tok)->type == T_WORD && (*tok)->next == NULL
		&& (*tok)->prev->type >= T_HERE_DOC)
	{
		*tok = head;
		return (head);
	}
	head = setup(tok, head, previous);
	return (head);
}
