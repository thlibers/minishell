/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:11 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 15:06:11 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <string.h>

t_token	*prompt(t_minishell minishell)
{
	t_token	*token;
	char	*line;

	token = NULL;
	line = readline("\x1b[0;32mminishell > \e[0m");
//	if (!line)
//	{
//		if (token)
//			free(token);
//		return (NULL);
//	}
	add_to_history(minishell.fd_history, line);
	free(line);
	return (token);
}
