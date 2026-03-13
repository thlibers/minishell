/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:16:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/13 16:09:33 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
