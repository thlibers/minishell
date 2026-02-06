/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:51:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/04 12:22:47 by thlibers         ###   ########.fr       */
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
	while ((line[len] && !is_operator(&line[len]) && line[len] != ' ')
		|| is_inquote(&quote, line[len]))
		len++;
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
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

t_data_type	assign_ope(char *c)
{
	t_data_type	type;

	type = T_NULL;
	if (c[0] == '|' && c[1] != '|') // PIPE
		type = T_PIPE;
	else if (c[0] == '|' && c[1] == '|') // OR
		type = T_OR;
	else if (c[0] == '<' && c[1] == '<') // HERE_DOC
		type = T_HERE_DOC;
	else if (c[0] == '<' && c[1] != '<') // IN
		type = T_RED_IN;
	else if (c[0] == '>' && c[1] == '>') // APP_OUT
		type = T_RED_OUT_APP;
	else if (c[0] == '>' && c[1] != '>') // OUT
		type = T_RED_OUT;
	else if (c[0] == '&' && c[1] == '&') // AND
		type = T_AND;
	return (type);
}

void	showtok(t_tok *tok)
{
	while (tok)
	{
		printf("enum val = %d\n", tok->type);
		printf("val = %s\n", tok->str);
		if (tok->prev)
			printf("prev val = %s\n", tok->prev->str);
		printf("-------\n");
		tok = tok->next;
	}
}

void	free_tok(t_tok **tok)
{
	t_tok	*save;

	while (*tok)
	{
		save = (*tok)->next;
		free((*tok)->str);
		free(*tok);
		*tok = save;
	}
}

void	*tokenizer(char *line)
{
	int		i;
	bool	states;
	int		quote;
	t_tok	*tok;
	t_ast	*ast;

	tok = NULL;
	i = 0;
	printf("--- BEGIN ---\n");
	while (line[i])
	{
		quote = 0;
		states = false;
		while (ft_isspace(line[i]) && line[i])
			i++;
		while (((!ft_isspace(line[i]) && !is_operator(&line[i])) || quote != 0)
			&& line[i])
		{
			is_inquote(&quote, line[i]);
			if (!states)
			{
				states = true;
				tok_create_back(&tok, T_WORD, &line[i]);
			}
			i++;
		}
		states = false;
		while (is_operator(&line[i]) != 0)
		{
			if (!states)
			{
				states = true;
				tok_create_back(&tok, assign_ope(&line[i]), &line[i]);
			}
			i++;
		}
	}
  check_quote(tok);
	ast = create_tree(tok);
	print_ast(ast);
  free_ast(&ast);
	free_tok(&tok);
	printf("--- END ---\n");
	return (NULL);
}
