/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:01:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 10:33:03 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_operator(char *word)
{
	if (word[0] == '|')
	{
		if (word[1] == '|')
			return (7);
		return (1);
	}
	else if (word[0] == '>')
	{
		if (word[1] == '>')
			return (2);
		return (3);
	}
	else if (word[0] == '<')
	{
		if (word[1] == '<')
			return (4);
		return (5);
	}
	else if (word[0] == '&')
		return (6);
	return (0);
}
