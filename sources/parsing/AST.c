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

bool  is_command(t_tok *tok)
{
	if (!(*tok)->prev && (*tok)->prev->type != T_WORD)
		return (true);
	return (false);
}

bool  is_argument(t_tok *tok)
{
	if ((*tok)->prev->type == T_WORD)
		return (true);
	return (false);
}

bool  is_file(t_tok *tok)
{
	if ((*tok)->prev->type != T_WORD || (*tok)->prev->type != T_FILE)
		return (true);
	return (false);
}

t_ast *create_branch(t_tok *tok)
{
	t_ast *ast;

	ast = calloc(1, sizeof(t_ast));
	ast->type = tok->
}

t_ast *create_tree(t_tok *tok)
{
	t_ast node;
	
	if (tok->next != NULL)
		tree = create_tree(tok);
	while (tok->prev->type == T_WORD || !tok->prev)
		tok = tok->prev;
	node = calloc(1, sizeof(t_ast));
	node->type = tok->prev->type;
	node->left_right = node;
	while (tok->type == T_WORD)
	{

	}
}

t_data_type	next_ope(t_tok *tok)
{
	while (tok)
	{
			if (tok->type != T_WORD)
				break ;

	}
	return (tok->type);
}

bool  AST(t_tok *tok)
{

	while (tok)
	{
		type = next_ope(tok);
	}

}
