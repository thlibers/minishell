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
