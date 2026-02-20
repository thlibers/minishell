/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:08 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/06 13:25:05 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	pipes_creation(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe_fd[i]) == -1)
			print_error("Pipe creation failed");
		i++;
	}
}

static void	pipes_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipe_fd[i][0]);
		close(pipex->pipe_fd[i][1]);
		pipex->pipe_fd[i][0] = -1;
		pipex->pipe_fd[i][1] = -1;
		i++;
	}
}

static void	children_creation(t_pipex *pipex, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			print_error("Fork creation failed");
		if (pid[i] == 0)
			child_process(pipex, i);
		i++;
	}
}

void	execute_pipex(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	pipex->pid = NULL;
	pipex->pid = ft_calloc(pipex->cmd_count, sizeof(int));
	if (!pipex->pid)
		print_error("Allocation pid array failed");
	pipex->pipe_fd = ft_calloc(pipex->cmd_count, sizeof(int *));
	if (!pipex->pipe_fd)
		print_error("Allocation Pipe_fd array failed");
	pipes_creation(pipex);
	children_creation(pipex, pipex->pid);
	pipes_close(pipex);
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pid[i], &status, 0);
		printf("%d\n", status);
		if (WIFEXITED(status))
			printf("exited, status=%d\n", WEXITSTATUS(status));
		i++;
	}
}
