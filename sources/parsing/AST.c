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
			return (tok->type);
		tok = tok->next;
	}
	return (T_WORD);
}

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
/*
int	cmd_count(t_ast *ast)
{
	int count;

	count = 0;
	if (!ast)
		return (0);
	count = cmd_count(ast->next);

}*/
/* --- DEBUG --- */
void  print_type(int leaf_number, t_ast *ast)
{
	switch (ast->type)
	{
		case 0:
			printf("leaf %d type T_NULL\n", leaf_number);
			break;
		case 1:
			printf("leaf %d type T_WORD\n", leaf_number);
			break;
		case 2:
			printf("leaf %d type T_HEREdOC\n", leaf_number);
			break;
		case 3:
			printf("leaf %d type T_RED_IN\n", leaf_number);
			break;
		case 4:
			printf("leaf %d type T_RED_OUT\n", leaf_number);
			break;
		case 5:
			printf("leaf %d type T_RED_OUT_APP\n", leaf_number);
			break;
		case 6:
			printf("leaf %d type T_LIMITER\n", leaf_number);
			break;
		case 7:
			printf("leaf %d type T_PIPE\n", leaf_number);
			break;
		case 8:
			printf("leaf %d type T_FILE\n", leaf_number);
			break;
		case 9:
			printf("leaf %d type T_AND\n", leaf_number);
			break;
		case 10:
			printf("leaf %d type T_OR\n", leaf_number);
			break;
		default:
			break;
	}
}

void	print_ast(t_ast *ast)
{
	t_ast	*leaf;
	int		leaf_number;

	leaf_number = 0;
	printf("--- AST DATA ---\n");
	while (ast)
	{
		leaf_number++;
		print_type(leaf_number, ast);
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
	printf("----------------\n");
}
