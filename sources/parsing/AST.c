/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:05:34 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/05 10:06:11 by nclavel          ###   ########.fr       */
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
/*
t_ast *create_branch(t_tok *tok)
{
	t_ast *ast;

	ast = calloc(1, sizeof(t_ast));
	ast->type = tok->
}

t_ast *create_tree(t_tok *tok)
{

}
*/
