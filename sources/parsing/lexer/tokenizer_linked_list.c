/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:16:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 17:58:14 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/prototypes.h"
#include <stdio.h>

char	*tok_str_save(char *line, t_data_type data_type)
{
	char	*str;
	int		quote;
	int		len;
	int		i;

	i = 0;
	quote = 0;
	len = 0;
	(void)data_type;
	while (line[len] && ((!is_operator(&line[len]) && !ft_isspace(line[len]))
			|| quote != 0))
	{
		is_inquote(&quote, line[len]);
		len++;
	}
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	return (str);
}

t_tok	*tok_create_back(t_tok **tok, t_data_type data_type, char *line)
{
	t_tok	*node;
	t_tok	*head;

	node = ft_calloc(1, sizeof(t_tok));
	if (!node)
		return (NULL);
	node->type = data_type;
	if (data_type == T_WORD)
		node->str = tok_str_save(line, data_type);
	if (data_type == T_WORD && !node->str)
		return (free(node), NULL);
	head = *tok;
	if (*tok == NULL)
		*tok = node;
	else
	{
		while ((*tok)->next)
			*tok = (*tok)->next;
		(*tok)->next = node;
		node->prev = *tok;
		*tok = head;
	}
	return (node);
}

t_tok	*setup(t_tok **tok, t_tok *head, t_tok *prev)
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
