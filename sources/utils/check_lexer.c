/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:01:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/23 17:01:27 by nclavel          ###   ########.fr       */
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

bool	is_quoted(char *word)
{
	if ()
}
