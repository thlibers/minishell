/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:16:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/26 17:18:47 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Sauvegarder la string pour les token en T_WORD
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
	while ((line[len] && !is_operator(&line[len]) && !ft_isspace(line[len]))
		|| quote != 0)
	{
		is_inquote(&quote, line[len]);
		len++;
	}
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Creer le token et l'ajouter a la suite de notre liste
t_tok	*tok_create_back(t_tok **tok, t_data_type data_type, char *line)
{
	t_tok	*node;
	t_tok	*head;

	node = calloc(1, sizeof(t_tok));
	if (!node)
		return (NULL);
	node->type = data_type;
	if (data_type == T_WORD)
		node->str = tok_str_save(line, data_type);
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
	return (head);
}

void	back_tofirst(t_tok **tok)
{
	t_tok	*cmd;
	t_tok	*last_arg;
	t_tok	*next_ope;
	t_tok	*head;
	t_tok	*save;
	
	head = *tok;
	while (*tok && (*tok)->next && ((*tok)->type >= T_HERE_DOC || ((*tok)->type == T_WORD && (*tok)->prev->type >= T_HERE_DOC)))
		*tok = (*tok)->next;
	if ((*tok)->type == T_WORD && (*tok)->next == NULL && (*tok)->prev->type >= T_HERE_DOC)
	{
		*tok = head;
		return ;
	}
	cmd = *tok;
	save = cmd->prev;
	while ((*tok)->next && (*tok)->next->type == T_WORD)
		*tok = (*tok)->next;
	last_arg = *tok;
	next_ope = (*tok)->next;
	head->prev = last_arg;
	last_arg->next = head;
	cmd->prev = NULL;
	save->next = next_ope;
	if (next_ope)
		next_ope->prev = save;
	*tok = cmd;
}
