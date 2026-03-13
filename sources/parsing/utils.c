/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:23:41 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/13 16:04:49 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_inquote(int *quote, char c)
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

// bool	is_in_quote(char *str, int card_loc)
// {
// 	bool	quote;
// 	int		i;

// 	quote = 0;
// 	i = 0;
// 	while (str[i] && i < card_loc)
// 	{
// 		if (str[i] == '"' && quote == false)
// 			quote = true;
// 		else if (str[i] == '"' && quote == true)
// 			quote = false;
// 		i++;
// 	}
// 	return (quote);
// }