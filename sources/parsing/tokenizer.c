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

void  *tokenize(char *line)
{
	int i;
	bool states;

	i = 0;
	printf("--- BEGIN ---\n");
	while (line[i])
	{
		states = false;
		while (ft_isspace(line[i]) && line[i])
			i++;
		while (!ft_isspace(line[i]) && is_operator(&line[i]) == 0 && line[i])
		{
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
				printf("T_OPE\n");
			}
			i++;
		}

	}
	printf("--- END ---\n");
	return (NULL);
}

// Ne gere pas les quotes