/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/27 15:06:06 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    full_clean(t_minishell *minishell)
{
        if (minishell->exec.pipe_fd)
                pipes_close(&minishell->exec);
        if (minishell->exec.cmd)
                free_tab(minishell->exec.cmd);
        if (minishell->exec.env)
                free_tab(minishell->exec.env);
        if (minishell->exec.infile_fd > 2)
                close(minishell->exec.infile_fd);
        if (minishell->exec.outfile_fd > 2)
                close(minishell->exec.outfile_fd);
        if (minishell->fd_history > 2)
                close(minishell->fd_history);
        if (minishell->ast)
                free_ast(&minishell->ast);
        if (minishell->pid)
                free(minishell->pid);
        if (minishell->env)
                env_clean(minishell->env, NULL);
}

void    half_clean(t_minishell *minishell)
{
        if (minishell->exec.pipe_fd)
                pipes_close(&minishell->exec);
        if (minishell->exec.infile_fd > 2)
                close(minishell->exec.infile_fd);
        if (minishell->exec.outfile_fd > 2)
                close(minishell->exec.outfile_fd);
        if (minishell->fd_history > 2)
                close(minishell->fd_history);
        if (minishell->ast)
                free_ast(&minishell->ast);
        if (minishell->pid)
                free(minishell->pid);
        if (minishell->env)
                env_clean(minishell->env, NULL);
}

void	clean_child(t_minishell *minishell, t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec || !minishell)
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
	if (minishell->pid)
		free(minishell->pid);
	if (minishell->exec.cmd)
		free_tab(minishell->exec.cmd);
	if (minishell->exec.env)
		free_tab(minishell->exec.env);
}

void	cleanup_pipe(t_minishell *minishell, t_exec *exec)
{
	int	i;

	i = 0;
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
	if (minishell->pid)
		free(minishell->pid);
}
