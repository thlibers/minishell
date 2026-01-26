/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 15:47:12 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_token	*create_token(char **word, int *stop_at)
{
	t_token	*node;
	int		i;

	token = calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	while (word[*stop_at])
	{
		i = 0;
		if (is_operator(word[stop_at]))
			node->T_NXT_OPE = ft_strdup(word[stop_at]);
		else if (ft_strchr(word[stop_at], "\0"))
			node->T_EOF = true;
		else if (!token->T_COMM)
			node->T_COMM = ft_strdup(word[stop_at]);
		else
		{
			while (!is_operator(word[stop_at] && word[stop_at]))
			{
				node->T_ARG[i] = word[stop_at];
				i++;
				(*stop_at)++;
			}
		}
		(*stop_at)++;
	}
	node->next = NULL;
}

void	print_token(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("--- TOKEN %d ---\n", i);
		printf("T_COMM = %s\n", head->T_COMM);
		printf("T_ARG = %s\n", head->T_ARG[0]);
		printf("T_OPE = %s\n", head->T_OPE);
		printf("T_FILE = %s\n", head->T_FILE);
		printf("T_NXT_OPE = %s\n", head->T_NXT_OPE);
		printf("T_EOF = %s\n", head->T_EOF);
		head = head->next;
		i++;
	}
}

static void	token_add_back(t_token **head, t_token *node)
{
	t_token	*checkpoint;

	checkpoint = *head;
	while ((*head)->next)
		*head = (*head)->next(*head)->next = node;
	*head = checkpoint;
}

t_token	lexer(char *line)
{
	t_token	*head;
	int		stop;

	stop = 0;
	head = calloc(1, t_token);
	if (!head)
		return (NULL);
	while (splitted[i])
	{
		head = create_token(splitted, &stop);
		i++;
	}
	return (token);
}
