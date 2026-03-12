/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 15:29:51 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clean_child(t_minishell *minishell, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec || !minishell)
		return ;
	if (exec->child.infile_fd > 2)
		(close(exec->child.infile_fd), exec->child.infile_fd = -1);
	if (exec->child.outfile_fd > 2)
		(close(exec->child.outfile_fd), exec->child.outfile_fd = -1);
	while (i < exec->cmdc)
	{
		if (exec->pipe_fd[i][0] > 2)
			(close(exec->pipe_fd[i][0]), exec->pipe_fd[i][0] = -1);
		if (exec->pipe_fd[i][1] > 2)
			(close(exec->pipe_fd[i][1]), exec->pipe_fd[i][1] = -1);
		i++;
	}
	if (exec->pipe_fd)
		free(exec->pipe_fd);
	if (minishell->pid)
		free(minishell->pid);
	if (minishell->exec.child.cmd)
		free_tab(minishell->exec.child.cmd);
	if (minishell->exec.env)
		free_tab(minishell->exec.env);
}

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
