/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:16:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/13 10:16:33 by nclavel          ###   ########.fr       */
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
