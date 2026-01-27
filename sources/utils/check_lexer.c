/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:01:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/27 10:57:49 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	is_operator(char *word)
{
	if (ft_strcmp(word, "|"))
		return (true);
	else if (ft_strcmp(word, ">>"))
		return (true);
	else if (ft_strcmp(word, ">"))
		return (true);
	else if (ft_strcmp(word, "<<"))
		return (true);
	else if (ft_strcmp(word, "<"))
		return (true);
	else if (ft_strcmp(word, "||"))
		return (true);
	else if (ft_strcmp(word, "&&"))
		return (true);
	return (false);
}

void	is_inquote(t_token *token, char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			j = 1;
			while(line[i + j] && line[i + j] != '"')
			{
				token->isquote = 2;
				j++;
			}
		}
		else if (line[i] == '\'')
		{
			j = 1;
			while(line[i + j] && line[i + j] != '\'')
			{
				token->isquote = 1;
				j++;
			}
		}
		i++;
		token->isquote = 0;
	}
}
