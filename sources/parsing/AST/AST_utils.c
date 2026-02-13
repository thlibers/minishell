/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_word_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:30 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/13 10:28:35 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Compter le nombre de commande dans notre ast
int	cmd_count(t_ast *ast)
{
	int	count;

	count = 0;
	if (!ast)
		return (0);
	count += cmd_count(ast->leaf_right);
	if (!ast->top && ast->leaf_left)
		count++;
	else if (ast->top && ast->top->type < T_HERE_DOC)
		count++;
	return (count);
}
