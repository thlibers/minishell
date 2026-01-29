/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:31:13 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 15:56:33 by thlibers         ###   ########.fr       */
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
	node->comm_args->arguments = calloc(10, sizeof(char *));
	if (!node->comm_args->arguments)
		return (free(node->comm_args), free(node), NULL);
	while (splitted[i])
	{
		if (!node->comm_args->command && !is_operator(splitted[i], &node))
			node->comm_args->command = ft_strdup(splitted[i]);
		else if (!is_operator(splitted[i], &node))
		{
			node->comm_args->arguments[j] = ft_strdup(splitted[i]);
			j++;
		}
		i++;
	}
	node->comm_args->arg_count = j;
	node->comm_args->arguments[j] = NULL;
	node->next = NULL;
	return (node);
}

void	clear_token(t_token **head)
{
	t_token	*save;
	int		i;

	while (*head)
	{
		i = 0;
		save = (*head)->next;
		if (head)
		{
			if ((*head)->comm_args)
			{
				if ((*head)->comm_args->arguments)
				{
					while ((*head)->comm_args->arguments[i])
						free((*head)->comm_args->arguments[i++]);
					free((*head)->comm_args->arguments);
				}
				if ((*head)->comm_args->command)
					free((*head)->comm_args->command);
				free((*head)->comm_args);
			}
			free(*head);
		}
		*head = save;
	}
}

static void	token_add_back(t_token **head, t_token *node)
{
	t_token	*checkpoint;

	checkpoint = *head;
	if (!*head)
	{
		*head = node;
		return ;
	}
	while ((*head)->next)
	{
		*head = (*head)->next;
	}
	(*head)->next = node;
	*head = checkpoint;
}

t_token	*lexer(t_minishell *minishell, char *line)
{
	t_token	*node;
	char	*tmp;
	char	**splitted;

	(void)minishell;
	tmp = ft_strtok(line, "|");
	while (tmp)
	{
		splitted = ft_splitnoquote(tmp, ' ');
		if (!splitted)
			return (NULL);
		node = create_token(splitted);
		printf("COMM = %s\n", node->comm_args->command);
		for (int i = 0; node->comm_args->arguments[i]; i++)
		{
			printf("ARG = %s\n", node->comm_args->arguments[i]); // DEBUG
		}
		token_add_back(&minishell->token, node);
		free_tab(splitted);
		tmp = ft_strtok(NULL, "|");
	}
	return (NULL);
}

// check des commandes de droite a gauche. + execution de gauche a droite
