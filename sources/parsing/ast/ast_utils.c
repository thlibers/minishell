/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:30 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/02 12:36:05 by thlibers         ###   ########.fr       */
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

bool check_pipe(t_ast *ast)
{
	while (ast->leaf_right)
	{
		if (ast->type == T_PIPE)
			return (true);
		ast = ast->leaf_right;
	}
	return(false);
}
