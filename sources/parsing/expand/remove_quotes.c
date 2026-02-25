/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:08:45 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/23 14:51:06 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_rm_quotes(t_quotes *q, char **str)
{
	q->first = -1;
	q->last = -1;
	q->quote_type = IN_RESET;
	q->len = ft_strlen(*str);
	q->i = q->len - 1;
}

static void	single_or_double(t_quotes *q, char **str)
{
	if ((*str)[q->i] == '\'' && q->quote_type == IN_RESET)
	{
		q->quote_type = IN_SINGLE_QUOTE;
		q->last = q->i;
	}
	else if ((*str)[q->i] == '\"' && q->quote_type == IN_RESET)
	{
		q->quote_type = IN_DOUBLE_QUOTE;
		q->last = q->i;
	}
}

void	remove_quotes(char **str)
{
	t_quotes	q;

	init_rm_quotes(&q, str);
	while (q.i >= 0)
	{
		if (((*str)[q.i] == '\'' || (*str)[q.i] == '\"')
				&& q.quote_type == IN_RESET)
			single_or_double(&q, str);
		else if (q.quote_type && ((*str)[q.i] == '\'' || (*str)[q.i] == '\"'))
		{
			q.first = q.i;
			ft_strlcpy(&(*str)[q.last], &(*str)[q.last + 1], q.len - 1);
			ft_strlcpy(&(*str)[q.first], &(*str)[q.first + 1], q.len - 1);
			if (q.len - 2 == 0)
				*str = ft_realloc(*str, 1);
			else
				*str = ft_realloc(*str, q.len - 2);
			q.len -= 2;
			(*str)[q.len] = '\0';
			q.quote_type = IN_RESET;
		}
		q.i--;
	}
}
