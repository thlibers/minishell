/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:05:34 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/06 17:08:42 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data_type	next_ope(t_tok *tok)
{
	while (tok)
	{
		if (tok->type != T_WORD)
			break ;
		tok = tok->next;
	}
	return (T_WORD);
}
/*
t_ast last_branch(t_tok)
{
	t_ast *branch;

	if (tok)
}
*/
t_ast	*create_left(t_tok *tok)
{
	t_ast	*left;
	t_ast	*back;

	if (!tok || tok->type != T_WORD)
		return (NULL);
	if (tok->type == T_WORD)
		back = create_left(tok->next);
	left = calloc(1, sizeof(t_ast));
	left->type = tok->type;
	left->data = ft_strdup(tok->str);
	left->leaf_left = back;
	return (left);
}

t_ast	*create_tree(t_tok *tok)
{
	t_ast	*node;
	t_ast	*tree;

	if (!tok)
		return (NULL);
	while (tok->next && tok->type != T_WORD)
		tok = tok->next;
	while (tok->next && tok->next->type == T_WORD)
		tok = tok->next;

	if (tok->type == T_WORD)
		tree = create_tree(tok->next);

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = next_ope(tok);
	node->leaf_right = tree;
	while (tok->prev && tok->prev->type == T_WORD)
		tok = tok->prev;
	node->leaf_left = create_left(tok);
	return (node);
}


/* --- DEBUG --- */
void	print_ast(t_ast *ast)
{
	t_ast	*leaf;
	int leaf_number = 0;

	while (ast)
	{
		leaf_number++;
		if (ast->leaf_left)
		{
			leaf = ast->leaf_left;
			while (leaf)
			{
				printf("leaf %d : %s\n", leaf_number, leaf->data);
				leaf = leaf->leaf_left;
			}
		}
		ast = ast->leaf_right;
	}
}
