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

bool	is_operator(char *word, t_token **node)
{
	if (ft_strcmp(word, "|") == 0)
		return ((*node)->type = T_PIPE, true);
	else if (ft_strcmp(word, ">>") == 0)
		return ((*node)->type = T_RED_OUT_APP, true);
	else if (ft_strcmp(word, ">") == 0)
		return ((*node)->type = T_RED_OUT, true);
	else if (ft_strcmp(word, "<<") == 0)
		return ((*node)->type = T_RED_IN_APP, true);
	else if (ft_strcmp(word, "<") == 0)
		return ((*node)->type = T_RED_IN, true);
	//	else if (ft_strcmp(word, "||") == 0)
	//		return ((*node)->type = T_OR, true);
	//	else if (ft_strcmp(word, "&&") == 0)
	//		return (true);
	return (false);
}
