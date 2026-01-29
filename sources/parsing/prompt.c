/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:11 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/29 12:47:18 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <string.h>

bool	prompt(t_minishell minishell)
{
	char	*line;

	line = readline("\x1b[0;32mminishell > \e[0m");
	if (!line)
		return (false);
	add_to_history(minishell.fd_history, line);
	lexer(&minishell, line);
	selector(&minishell);
	free(line);
	return (true);
}
