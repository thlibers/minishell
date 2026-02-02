/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:51:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 10:16:09 by thlibers         ###   ########.fr       */
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
/*
void  assign_ope(char c)
{
	if (c == '|')

}
*/

void  *tokenizer(char *line)
{
	int i;
	bool states;
	int quote;

	i = 0;
	printf("--- BEGIN ---\n");
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
				printf("T_WORD\n");
			}
			i++;
		}
		states = false;
		while (is_operator(&line[i]) != 0)
		{
			if (!states)
			{
				states = true;
				if (line[i] == '|')
					printf("T_PIPE\n");
				else
					printf("T_OPE\n");
			}
			i++;
		}
	}
	printf("--- END ---\n");
	return (NULL);
}
