/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:27:05 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/06 06:12:43 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	full_clean(t_minishell *minishell)
{
	if (minishell->exec.save_std[0] > 2)
		(close(minishell->exec.save_std[0]), minishell->exec.save_std[0] = -1);
	if (minishell->exec.save_std[1] > 2)
		(close(minishell->exec.save_std[1]), minishell->exec.save_std[1] = -1);
	if (minishell->exec.pipe_fd)
		pipes_close(&minishell->exec);
	if (minishell->exec.cmd)
		free_tab(minishell->exec.cmd);
	if (minishell->exec.env)
		free_tab(minishell->exec.env);
	if (minishell->exec.infile_fd > 2)
		(close(minishell->exec.infile_fd), minishell->exec.infile_fd = -1);
	if (minishell->exec.outfile_fd > 2)
		(close(minishell->exec.outfile_fd), minishell->exec.outfile_fd = -1);
	if (minishell->fd_history > 2)
		(close(minishell->fd_history), minishell->fd_history = -1);
	if (minishell->ast)
		free_ast(&minishell->ast);
	if (minishell->pid)
	{
		free(minishell->pid);
		minishell->pid = NULL;
	}
	if (minishell->env)
		env_clean(minishell->env, NULL);
}

void	half_clean(t_minishell *minishell)
{
	if (minishell->exec.save_std[0] > 2)
		(close(minishell->exec.save_std[0]), minishell->exec.save_std[0] = -1);
	if (minishell->exec.save_std[1] > 2)
		(close(minishell->exec.save_std[1]), minishell->exec.save_std[1] = -1);
	if (minishell->exec.infile_fd > 2)
		(close(minishell->exec.infile_fd), minishell->exec.infile_fd = -1);
	if (minishell->exec.outfile_fd > 2)
		(close(minishell->exec.outfile_fd), minishell->exec.outfile_fd = -1);
	if (minishell->fd_history > 2)
		(close(minishell->fd_history), minishell->fd_history = -1);
	if (minishell->ast)
		free_ast(&minishell->ast);
	if (minishell->pid)
		(free(minishell->pid), minishell->pid = NULL);
	if (minishell->env)
		env_clean(minishell->env, NULL);
}

void	cleanup_pipe(t_minishell *minishell, t_exec *exec)
{
	int	i;

	i = 0;
	if (minishell->pid)
		free(minishell->pid);
	if (!exec)
		return ;
	if (exec->infile_fd > 2)
		(close(exec->infile_fd), exec->infile_fd = -1);
	if (exec->outfile_fd > 2)
		(close(exec->outfile_fd), exec->outfile_fd = -1);
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
}
