/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:30:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 12:37:46 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	one_command_only(t_exec *exec, int child_number)
{
	(void)child_number;
	if (exec->infile_fd > 2)
	{
		if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (exec->infile_fd > 2)
			(close(exec->infile_fd), exec->infile_fd = -1);
	}
	if (exec->outfile_fd > 2)
	{
		if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (exec->outfile_fd > 2)
			(close(exec->outfile_fd), exec->outfile_fd = -1);
	}
}

static void	first_command(t_exec *exec, int child_number, int is_child)
{
	(void)is_child;
	if (exec->infile_fd > 2)
	{
		if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (exec->infile_fd > 2)
			(close(exec->infile_fd), exec->infile_fd = -1);
	}
	if (exec->outfile_fd > 2)
	{
		if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		if (exec->outfile_fd > 2)
			(close(exec->outfile_fd), exec->outfile_fd = -1);
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
		first_command(exec, child_number, is_child);
	else if (child_number == exec->cmdc - 1)
	{
		if (exec->infile_fd > 2)
		{
			if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
			close(exec->infile_fd);
			exec->infile_fd = -1;

		}
		else
		{
			if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
		}
		if (exec->outfile_fd > 2)
		{
			if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, EDUP2);
			if (exec->outfile_fd > 2)
				(close(exec->outfile_fd), exec->outfile_fd = -1);
		}
		if (is_child && exec->pipe_fd[child_number - 1][0] > 2)
			(close(exec->pipe_fd[child_number - 1][0]),
				exec->pipe_fd[child_number - 1][0] = -1);
		if (is_child && exec->pipe_fd[child_number - 1][1] > 2)
			(close(exec->pipe_fd[child_number - 1][1]),
				exec->pipe_fd[child_number - 1][1] = -1);
	}
}

static void	setup_middle_commands(t_exec *exec, int child_number, int is_child)
{
	(void)is_child;
	if (exec->infile_fd > 2)
	{
		if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		close(exec->infile_fd);
		exec->infile_fd = -1;
	}
	else
	{
		if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
	}
	if (exec->outfile_fd > 2)
	{
		if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, EDUP2);
		close(exec->outfile_fd);
		exec->outfile_fd = -1;
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

	if (!is_child)
	{
		exec->save[0] = dup(STDIN_FILENO);
		exec->save[1] = dup(STDOUT_FILENO);
	}
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
	}
}
