/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:11 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/04 23:23:33 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include <string.h>

t_token	*tokenizer(char *line)
{
	t_token *token;

	token = NULL;
	if (!line)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	memset(&token, 0, sizeof(token));
	puts(line);
	return (token);
}

t_token	*prompt(void)
{
	t_token	*token;
	char	*line;

	token = NULL;
	line = readline("\x1b[0;32mmsh > \e[0m");
	if (!line)
	{
		if (token)
			free(token);
		return (NULL);
	}
	token = tokenizer(line);
	add_history(line);
	free(line);
	return (token);
}
