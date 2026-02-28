/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:51:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/26 17:35:07 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Trouver de quelle operateur notre token est
static t_data_type	assign_ope(char *c)
{
	t_data_type	type;

	type = T_NULL;
	if (c[0] == '|' && c[1] != '|')
		type = T_PIPE;
	else if (c[0] == '|' && c[1] == '|')
		type = T_OR;
	else if (c[0] == '<' && c[1] == '<')
		type = T_HERE_DOC;
	else if (c[0] == '<' && c[1] != '<')
		type = T_RED_IN;
	else if (c[0] == '>' && c[1] == '>')
		type = T_RED_OUT_APP;
	else if (c[0] == '>' && c[1] != '>')
		type = T_RED_OUT;
	else if (c[0] == '&' && c[1] == '&')
		type = T_AND;
	return (type);
}

// Creer notre token de type T_WORD
static bool	create_tok_word(int *i, char *line, t_tok **tok)
{
	int		quote;
	bool	states;

	quote = 0;
	states = false;
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	while (((!ft_isspace(line[*i]) && !is_operator(&line[*i])) || quote != 0)
		&& line[*i])
	{
		is_inquote(&quote, line[*i]);
		if (!states)
		{
			states = true;
			if (!tok_create_back(tok, T_WORD, &line[*i]))
				return (false);
		}
		(*i)++;
	}
	return (true);
}

// Creer notre token d'operateur ; ope++ fix probablement temp |||
static bool	create_tok_ope(int *i, char *line, t_tok **tok)
{
	int		ope;
	bool	states;

	ope = 0;
	states = false;
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	while (is_operator(&line[*i]) != 0 && ope < 2)
	{
		ope++;
		if (!states)
		{
			states = true;
			if (!tok_create_back(tok, assign_ope(&line[*i]), &line[*i]))
				return (false);
		}
		(*i)++;
	}
	return (true);
}

// Coeur de la fonction du tokenizer
t_tok	*tokenizer(char *line)
{
	int		i;
	t_tok	*tok;

	i = 0;
	tok = NULL;
	while (line[i])
	{
		if (!create_tok_word(&i, line, &tok))
			return (NULL);
		if (!create_tok_ope(&i, line, &tok))
			return (NULL);
	}
	if (!check_quote(tok) || !check_ope(tok))
		return (free_tok(&tok), NULL);
	if (tok->type >= T_HERE_DOC)
		back_tofirst(&tok);
	return (tok);
}

// DEBUG
void	print_tok(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		printf("%d; %s; %d\n", i, tok->str, tok->type);
		i++;
		tok = tok->next;
	}
}
