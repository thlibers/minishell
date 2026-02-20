/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:23:41 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/20 11:24:36 by nclavel          ###   ########.fr       */
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

void	free_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}
