/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:30:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/25 15:36:58 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	one_command_only(t_exec *exec, int child_number)
{
	(void)child_number;
	if (exec->infile_fd > 2)
	{
		if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, "dup2 failed for pipe read");
		close(exec->infile_fd);
	}
	if (exec->outfile_fd > 2)
	{
		if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, "dup2 failed for outfile");
		close(exec->outfile_fd);
	}
}

static void	first_last_command(t_exec *exec, int child_number)
{
	if (child_number == 0)
	{
		if (exec->infile_fd > 2)
		{
			if (dup2(exec->infile_fd, STDIN_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, "dup2 failed for pipe read");
			close(exec->infile_fd);
		}
		if (dup2(exec->pipe_fd[child_number][1], STDOUT_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, "dup2 failed for outfile");
	}
	else if (child_number == exec->cmdc - 1)
	{
		if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
			ft_fprintf(STDERR_FILENO, "dup2 failed for pipe read");
		if (exec->outfile_fd > 2)
		{
			if (dup2(exec->outfile_fd, STDOUT_FILENO) == -1)
				ft_fprintf(STDERR_FILENO, "dup2 failed for outfile");
			close(exec->outfile_fd);
		}
		close(exec->pipe_fd[child_number - 1][0]);
		close(exec->pipe_fd[child_number - 1][1]);
	}
}

static void	setup_middle_commands(t_exec *exec, int child_number)
{
	if (dup2(exec->pipe_fd[child_number - 1][0], STDIN_FILENO) == -1)
		ft_fprintf(STDERR_FILENO, "dup2 failed for pipe read");
	if (dup2(exec->pipe_fd[child_number][1], STDOUT_FILENO) == -1)
		ft_fprintf(STDERR_FILENO, "dup2 failed for pipe write");
	close(exec->pipe_fd[child_number - 1][0]);
	close(exec->pipe_fd[child_number - 1][1]);
	close(exec->pipe_fd[child_number][0]);
	close(exec->pipe_fd[child_number][1]);
}

static void	init_child(t_exec *exec, int child_number)
{
	int	i;

	i = 0;
	if ((child_number == 0 && child_number == exec->cmdc - 1))
		one_command_only(exec, child_number);
	else if (child_number == 0 || child_number == exec->cmdc - 1)
		first_last_command(exec, child_number);
	else
		setup_middle_commands(exec, child_number);
	i = 0;
	while (i < exec->cmdc - 1)
	{
		if (i != child_number - 1 && i != child_number)
		{
			close(exec->pipe_fd[i][0]);
			close(exec->pipe_fd[i][1]);
		}
		i++;
	}
}

void	child_process(t_minishell *minishell, int child_number)
{
	char	*cmd_path;

	// testexe(&minishell->exec);
	init_child(&minishell->exec, child_number);
	//selector
	cmd_path = find_command_path(minishell, minishell->exec.delete_me[0]);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, "Minishell: %s: command not found\n", minishell->exec.delete_me[0]);
		ft_clear(minishell);
		exit(127);
	}
	if (execve(cmd_path, minishell->exec.delete_me, minishell->exec.env) == -1)
	{
		ft_fprintf(STDERR_FILENO, "execve failed");
		ft_clear(minishell);
		exit(126);
	}
	free(cmd_path);
}
