/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/25 12:25:02 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_clear(t_minishell *minishell)
{
	env_clean(minishell->env, NULL);
	close(minishell->fd_history);
	// free_ast(&minishell->root);
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

void	env_clean(t_env *env, char **tab)
{
	t_env	*checkpoint;

	if (env)
	{
		while (env)
		{
			checkpoint = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = checkpoint;
		}
	}
	if (tab)
	{
		free(tab[0]);
		free(tab[1]);
		free(tab);
	}
}

void	free_ast(t_ast **ast)
{
	t_ast	*save;
	t_ast	*leaf;

	if (*ast != NULL)
		free_ast(&(*ast)->leaf_right);
	if (*ast)
	{
		if ((*ast)->leaf_left)
		{
			leaf = (*ast)->leaf_left;
			while (leaf)
			{
				save = leaf->leaf_left;
				if (leaf)
					free(leaf->data);
				free(leaf);
				leaf = save;
			}
		}
		free(*ast);
	}
}

void	free_tok(t_tok **tok)
{
	t_tok	*save;

	while (*tok)
	{
		save = (*tok)->next;
		free((*tok)->str);
		free(*tok);
		*tok = save;
	}
}
