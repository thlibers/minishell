/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:27:19 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 16:08:30 by thlibers         ###   ########.fr       */
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

void	clean_heredoc_fd(t_exec *exec)
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

void	clean_files_fd(t_exec *exec)
{
	int	i;

	i = 0;
	if (exec->files.fd_arr)
	{
		while (i < exec->files.fd_size)
		{
			close(exec->files.fd_arr[i]);
			exec->files.fd_arr[i] = -1;
		}
		free(exec->files.fd_arr);
	}
}

void	cleanup_pipe(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return ;
	if (*exec->child.infile_fd > 2)
		(close(*exec->child.infile_fd), *exec->child.infile_fd = -1);
	if (*exec->child.outfile_fd > 2)
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
		free(exec->pipe_fd);
}
