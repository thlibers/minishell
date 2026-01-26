/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/26 15:50:52 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_token	*create_token(char *line)
{
	t_token	*node;
	int		i;

	node = calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
}

void	print_token(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		printf("--- TOKEN %d ---\n", i);
		printf("data = %s\n", head->data);
		printf("e_data = %s\n", head->type);
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
	t_token	*node;
	int		i;

	i = 0;
	head = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		node = create_token(line);
		token_add_back(&head, node);
		i++;
	}
	return (token);
}
