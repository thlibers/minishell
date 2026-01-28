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


static t_token	*create_token(char **splitted)
{
	t_token	*node;
	int		i;
	int		j;

	i = 0;
	j = 0;
	node = calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->comm_args = calloc(1, sizeof(t_token));
	if (!node->comm_args)
		return (free(node), NULL);
	while (splitted[i])
	{
		if (!node->comm_args->command && !is_operator(splitted[i]))
			node->comm_args->command = ft_strdup(splitted[i]);
		else if (!is_operator(splitted[i]))
		{
			node->comm_args->arguments[j] = ft_strdup(splitted[i]);
			j++;
		}
		i++;
	}
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
	char	**splitted;

	tmp = ft_strtok(line, "|");
	while (tmp)
	{
		tmp = ft_strtrim(tmp, " ");
		splitted = ft_splitnoquote(tmp, ' ')
		if (!splitted)
			return (NULL);
		printf("%s\n", tmp);
		tmp = ft_strtok(NULL, "|");
	}
	return (NULL);
}
