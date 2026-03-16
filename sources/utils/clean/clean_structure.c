/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 08:52:47 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/prototypes.h"

void	ptr_env_clean(t_env **env, char **tab)
{
	t_env	*checkpoint;

	if (env && *env)
	{
		while (env && *env)
		{
			checkpoint = (*env)->next;
			free((*env)->name);
			free((*env)->value);
			free(*env);
			*env = checkpoint;
		}
		*env = NULL;
	}
	if (tab)
	{
		free(tab[0]);
		free(tab[1]);
		free(tab);
		tab = NULL;
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
				if (leaf->data)
					free(leaf->data);
				free(leaf);
				leaf = save;
			}
		}
		free(*ast);
	}
	*ast = NULL;
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
	*tok = NULL;
}
