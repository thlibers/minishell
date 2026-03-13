/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:30:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/13 13:09:43 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	one_command_only(t_exec *exec, int child_number)
{
	(void)child_number;
	if (exec->files.fd_arr && *exec->child.infile_fd > 2)
	{
		if (dup2(*exec->child.infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (*exec->child.infile_fd > 2)
			(close(*exec->child.infile_fd), *exec->child.infile_fd = -1);
	}
	if (exec->files.fd_arr && *exec->child.outfile_fd > 2)
	{
		if (dup2(*exec->child.outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (*exec->child.outfile_fd > 2)
			(close(*exec->child.outfile_fd), *exec->child.outfile_fd = -1);
	}
}

static void	first_command(t_exec *exec, int child_number)
{
	if (exec->files.fd_arr && *exec->child.infile_fd > 2)
	{
		if (dup2(*exec->child.infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		(close(*exec->child.infile_fd), *exec->child.infile_fd = -1);
	}
	if (exec->files.fd_arr && *exec->child.outfile_fd > 2)
	{
		if (dup2(*exec->child.outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		(close(*exec->child.outfile_fd), *exec->child.outfile_fd = -1);
	}
	else
	{
		if (dup2(exec->pipe_fd[child_number][1], STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
	}
}

static void	first_last_command(t_exec *exec, int child_number, int is_child)
{
	if (child_number == 0)
		first_command(exec, child_number);
	else if (child_number == exec->cmdc - 1)
	{
		if (exec->files.fd_arr && *exec->child.infile_fd > 2)
		{
			if (dup2(*exec->child.infile_fd, STDIN_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
			close(*exec->child.infile_fd);
			*exec->child.infile_fd = -1;
		}
		else
		{
			if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
		}
		if (exec->files.fd_arr && *exec->child.outfile_fd > 2)
		{
			if (dup2(*exec->child.outfile_fd, STDOUT_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
			if (*exec->child.outfile_fd > 2)
				(close(*exec->child.outfile_fd), *exec->child.outfile_fd = -1);
		}
		clean_pipe_fd(exec, child_number, is_child);
	}
}

static void	setup_middle_commands(t_exec *exec, int child_number, int is_child)
{
	(void)is_child;
	if (exec->files.fd_arr && *exec->child.infile_fd > 2)
	{
		if (dup2(*exec->child.infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		close(*exec->child.infile_fd);
		*exec->child.infile_fd = -1;
	}
	else
	{
		if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
	}
	if (exec->files.fd_arr && *exec->child.outfile_fd > 2)
	{
		if (dup2(*exec->child.outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		close(*exec->child.outfile_fd);
		*exec->child.outfile_fd = -1;
	}
	else
	{
		if (dup2(exec->pipe_fd[child_number][1], STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
	}
}

void	init_child(t_exec *exec, int child_number, int is_child)
{
	int	i;

	child_save(exec, is_child);
	if ((child_number == 0 && child_number == exec->cmdc - 1))
		one_command_only(exec, child_number);
	else if (child_number == 0 || child_number == exec->cmdc - 1)
		first_last_command(exec, child_number, is_child);
	else
		setup_middle_commands(exec, child_number, is_child);
	if (is_child)
	{
		i = 0;
		while (i < exec->cmdc - 1)
		{
			if (exec->pipe_fd[i][0] > 2)
				(close(exec->pipe_fd[i][0]), exec->pipe_fd[i][0] = -1);
			if (exec->pipe_fd[i][1] > 2)
				(close(exec->pipe_fd[i][1]), exec->pipe_fd[i][1] = -1);
			i++;
		}
		clean_heredoc_fd(exec);
	}
}
