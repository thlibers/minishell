/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:51:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/03 17:34:04 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#define IN_RESET 0
#define IN_SINGLE_QUOTE 1
#define IN_DOUBLE_QUOTE 2


int	quote_id(char c, int *quote)
{
	if (c == '\"')
	{
		if (*quote == IN_DOUBLE_QUOTE)
			*quote = IN_RESET;
		else if (*quote == IN_RESET)
			*quote = IN_DOUBLE_QUOTE;
	}
	else if (c == '\'')
	{
		if (*quote == IN_SINGLE_QUOTE)
			*quote = IN_RESET;
		else if (*quote == IN_RESET)
			*quote = IN_SINGLE_QUOTE;
	}
	else if (c == '\0')
		*quote = IN_RESET;
	return (*quote);
}

t_tok *tok_create_back(t_tok **tok, t_data_type data_type)
{
	t_tok *node;
	t_tok *head;

	node = calloc(1, sizeof(t_tok));
	if (!node)
		return (NULL);
	node->type = data_type;
	node->next = NULL;
	head = *tok;
	if (*tok == NULL)
		*tok = node;
	else
	{
		while ((*tok)->next)
			*tok = (*tok)->next; 
		(*tok)->next = node;
		*tok = head;
	}
	return (head);
}

t_data_type  assign_ope(char *c)
{
	t_data_type	type;

	if (c[0] == '|' && c[1] != '|')		  // PIPE
		type = T_PIPE;
	else if (c[0] == '|' && c[1] == '|') // OR
		type = T_OR;
	else if (c[0] == '<' && c[1] == '<') // APP_IN
		type = T_RED_IN_APP;
	else if (c[0] == '<' && c[1] != '<')  // IN
		type = T_RED_IN;
	else if (c[0] == '>' && c[1] == '>') // APP_OUT
		type = T_RED_OUT_APP;
	else if (c[0] == '>' && c[1] != '>')  // OUT
		type = T_RED_OUT;
	else if (c[0] == '&' && c[1] == '&')  // AND
		type = T_AND;
	return (type);
}


void  showtok(t_tok *tok)
{
	while (tok)
	{
		printf("enum val = %d\n", tok->type);
		tok = tok->next;
	}
}

void  free_tok(t_tok **tok)
{
	t_tok *save;

	while (*tok)
	{
		save = (*tok)->next;
		free(*tok);
		*tok = save;
	}
}

void  *tokenizer(char *line)
{
	int i;
	bool states;
	int quote;
	t_tok *tok = NULL;

	i = 0;
	while (line[i])
	{
		quote = 0;
		states = false;
		while (ft_isspace(line[i]) && line[i])
			i++;
		while (((!ft_isspace(line[i]) && !is_operator(&line[i])) || quote != 0) && line[i])
		{
			is_inquote(&quote, line[i]);
			if (!states)
			{
				states = true;
				tok_create_back(&tok, T_WORD);
			}
			i++;
		}
		states = false;
		while (is_operator(&line[i]) != 0)
		{
			if (!states)
			{
				states = true;
				tok_create_back(&tok, assign_ope(&line[i]));
			}
			i++;
		}
	}
	showtok(tok);
	free_tok(&tok);
	return (NULL);
}
