/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chose_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:51:09 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/16 14:16:39 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static bool	chose_redin_redout(t_exec *exec, t_ast *ast)
{
	if ((ast)->type == T_RED_IN)
	{
		if (!file_opener(exec, ast, 0, &open_infile))
			return (false);
	}
	else if ((ast)->type == T_RED_OUT)
	{
		if (!file_opener(exec, ast, 1, &open_outfile))
			return (false);
	}
	else if ((ast)->type == T_RED_OUT_APP)
	{
		if (!file_opener(exec, ast, 0, &open_outfile))
			return (false);
	}
	return (true);
}

bool	redirection_choser(t_exec *exec, t_ast *ast)
{
	if (ast && ast->type == T_PIPE && ast->top && ast->top->type >= T_HERE_DOC)
		ast = ast->leaf_right;
	while (ast && (ast)->leaf_right && (ast)->type >= T_HERE_DOC)
	{
		if (!chose_redin_redout(exec, ast))
			return (false);
		else if ((ast)->type == T_HERE_DOC)
		{
			exec->child.infile_fd = &exec->files.hd_fd[exec->files.hd_fd_done];
			exec->files.hd_fd_done++;
		}
		if ((ast)->leaf_right->type == T_WORD)
			break ;
		ast = (ast)->leaf_right;
	}
	return (true);
}
