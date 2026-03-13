/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/13 15:40:25 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	close_file(t_exec *exec, t_ast *curr_branch)
{
	if (curr_branch->type >= T_HERE_DOC && curr_branch->leaf_right
		&& curr_branch->leaf_right->type < T_HERE_DOC)
	{
		if (exec->child.infile_fd > 2 && curr_branch->type >= T_RED_IN)
		{
			close(exec->child.infile_fd);
			exec->child.infile_fd = 0;
		}
		if (exec->child.outfile_fd > 2 && (curr_branch->type == T_RED_OUT
				|| curr_branch->type == T_RED_OUT_APP))
		{
			close(exec->child.outfile_fd);
			exec->child.outfile_fd = 1;
		}
	}
}
