/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:27:05 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 16:23:16 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clean_useless_child(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->exec.files.hd_fd_size)
	{
		if (minishell->exec.files.hd_fd[i] > 2)
		{
			close(minishell->exec.files.hd_fd[i]);
			minishell->exec.files.hd_fd[i] = -1;
		}
		i++;
	}
	if (minishell->exec.limiter)
		(free(minishell->exec.limiter), minishell->exec.limiter = NULL);
	if (minishell->exec.pipe_fd)
		pipes_close(&minishell->exec);
	if (minishell->fd_history > 2)
		(close(minishell->fd_history), minishell->fd_history = -1);
	if (minishell->ast)
		free_ast(&minishell->ast);
	if (minishell->pid)
		(free(minishell->pid), minishell->pid = NULL);
	if (minishell->env)
		env_clean(minishell->env, NULL);
}

void	full_clean(t_minishell *minishell)
{
	if (minishell->exec.limiter)
		(free(minishell->exec.limiter), minishell->exec.limiter = NULL);
	if (minishell->exec.child.save[0] > 2)
		(close(minishell->exec.child.save[0]), minishell->exec.child.save[0]
			= -1);
	if (minishell->exec.child.save[1] > 2)
		(close(minishell->exec.child.save[1]), minishell->exec.child.save[1]
			= -1);
	if (minishell->exec.child.cmd)
		free_tab(minishell->exec.child.cmd);
	if (minishell->exec.env)
		free_tab(minishell->exec.env);
	if (minishell->exec.child.infile_fd > 2)
		(close(minishell->exec.child.infile_fd),
			minishell->exec.child.infile_fd = -1);
	if (minishell->exec.child.outfile_fd > 2)
		(close(minishell->exec.child.outfile_fd),
			minishell->exec.child.outfile_fd = -1);
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
	clean_heredoc_fd(&minishell->exec);
	if (minishell->exec.child.save[0] > 2)
		(close(minishell->exec.child.save[0]), minishell->exec.child.save[0]
			= -1);
	if (minishell->exec.child.save[1] > 2)
		(close(minishell->exec.child.save[1]), minishell->exec.child.save[1]
			= -1);
	if (minishell->exec.child.infile_fd > 2)
		(close(minishell->exec.child.infile_fd),
			minishell->exec.child.infile_fd = -1);
	if (minishell->exec.child.outfile_fd > 2)
		(close(minishell->exec.child.outfile_fd),
			minishell->exec.child.outfile_fd = -1);
	if (minishell->fd_history > 2)
		(close(minishell->fd_history), minishell->fd_history = -1);
	if (minishell->exec.pipe_fd)
		cleanup_pipe(&minishell->exec);
	if (minishell->ast)
		free_ast(&minishell->ast);
	if (minishell->pid)
		(free(minishell->pid), minishell->pid = NULL);
	if (minishell->env)
		env_clean(minishell->env, NULL);
}

void	clean_heredoc(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->exec.files.hd_fd_size)
	{
		if (minishell->exec.files.hd_fd[i] > 2)
		{
			close(minishell->exec.files.hd_fd[i]);
			minishell->exec.files.hd_fd[i] = -1;
		}
		i++;
	}
	if (minishell->fd_history > 2)
		(close(minishell->fd_history), minishell->fd_history = -1);
	if (minishell->exec.env)
		(ptr_free_tab(&minishell->exec.env), minishell->exec.env = NULL);
	if (minishell->env)
		(env_clean(minishell->env, NULL), minishell->env = NULL);
	if (minishell->ast)
		(free_ast(&minishell->ast), minishell->ast = NULL);
}

void	pipes_close(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmdc - 1)
	{
		if (exec->pipe_fd[i][0] > 2)
			(close(exec->pipe_fd[i][0]), exec->pipe_fd[i][0] = -1);
		if (exec->pipe_fd[i][1] > 2)
			(close(exec->pipe_fd[i][1]), exec->pipe_fd[i][1] = -1);
		i++;
	}
	if (exec->pipe_fd)
		free(exec->pipe_fd);
	exec->pipe_fd = NULL;
}

void	cleanup_pipe(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
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
}
