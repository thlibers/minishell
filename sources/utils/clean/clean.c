/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:27:19 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 14:18:36 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ptr_free_tab(char ***arr)
{
	int	i;

	i = 0;
	if (!*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	close_files_fd(t_exec *exec)
{
	if (exec->files.fd_arr[0] > 2)
	{
		close(exec->files.fd_arr[0]);
		exec->files.fd_arr[0] = -1;
	}
	if (exec->files.fd_arr[1] > 2)
	{
		close(exec->files.fd_arr[1]);
		exec->files.fd_arr[1] = -1;
	}
}

void	close_heredoc_fd(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->files.hd_fd_size)
	{
		if (exec->files.hd_fd[i] > 2)
		{
			close(exec->files.hd_fd[i]);
			exec->files.hd_fd[i] = -1;
		}
		i++;
	}
}

void	cleanup_pipe(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return ;
	if (exec->child.infile_fd && *exec->child.infile_fd > 2)
		(close(*exec->child.infile_fd), *exec->child.infile_fd = -1);
	if (exec->child.outfile_fd && *exec->child.outfile_fd > 2)
		(close(*exec->child.outfile_fd), *exec->child.outfile_fd = -1);
	while (i < exec->cmdc)
	{
		if (exec->pipe_fd[i][0] > 2)
			(close(exec->pipe_fd[i][0]), exec->pipe_fd[i][0] = -1);
		if (exec->pipe_fd[i][1] > 2)
			(close(exec->pipe_fd[i][1]), exec->pipe_fd[i][1] = -1);
		i++;
	}
	if (exec->pipe_fd)
		(free(exec->pipe_fd), exec->pipe_fd = NULL);
}

void	clear_exec(t_minishell *minishell)
{
	if (minishell->pid)
		(free(minishell->pid), minishell->pid = NULL);
	if (minishell->exec.env)
		ptr_free_tab(&minishell->exec.env);
	if (minishell->exec.limiter)
		free(minishell->exec.limiter);
	if (minishell->exec.child.cmd)
		ptr_free_tab(&minishell->exec.child.cmd);
	if (minishell->exec.child.infile_fd && *minishell->exec.child.infile_fd > 2)
		(close(*minishell->exec.child.infile_fd),
			*minishell->exec.child.infile_fd = -1);
	if (minishell->exec.child.outfile_fd
		&& *minishell->exec.child.outfile_fd > 2)
		(close(*minishell->exec.child.outfile_fd),
			*minishell->exec.child.outfile_fd = -1);
	if (minishell->exec.pipe_fd)
		pipes_close(&minishell->exec);
	close_heredoc_fd(&minishell->exec);
}
