/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/26 17:47:59 by nclavel          ###   ########.fr       */
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

void  clear_token(t_token **head)
{
	t_token	*save;

	while (*head)
	{
		save = (*head)->next;
		
		head = save;
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

t_token	*lexer(t_minishell *minishell, char *line)
{
	char	*tmp;

	(void)minishell;
	tmp = ft_strtok(line, "|");
	while (tmp)
	{
		tmp = ft_strtrim(tmp, " ");
		printf("%s\n", tmp);
		tmp = ft_strtok(NULL, "|");
	}
	return (NULL);
}
