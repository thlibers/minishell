/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:08 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/25 15:28:20 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	pipes_creation(t_exec *exec)
{
	int	i;

	i = 0;
	exec->pipe_fd = ft_calloc(exec->cmdc, sizeof(int *));
	if (!exec->pipe_fd)
		ft_fprintf(STDERR_FILENO, "Allocation Pipe_fd array failed");
	while (i < exec->cmdc - 1)
	{
		if (pipe(exec->pipe_fd[i]) == -1)
			ft_fprintf(STDERR_FILENO, "Pipe creation failed");
		i++;
	}
}

static void	testexe(t_exec *exec, int i) // delete
{
	if (i == 0)
	{
		exec->delete_me = malloc(sizeof(char *) * 2);
		exec->delete_me[0] = ft_strdup("ls");
		exec->delete_me[1] = NULL;
	}
	
	if (i == 1)
	{
		exec->delete_me = malloc(sizeof(char *) * 3);
		exec->delete_me[0] = ft_strdup("grep");
		exec->delete_me[1] = ft_strdup("file");
		exec->delete_me[2] = NULL;
	}
}

static void	children_creation(t_minishell *minishell, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < minishell->exec.cmdc)
	{
		testexe(&minishell->exec, i);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_fprintf(STDERR_FILENO, "Fork creation failed");
		if (pid[i] == 0)
			child_process(minishell, i);
		i++;
	}
}

static void	pipes_close(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmdc - 1)
	{
		close(exec->pipe_fd[i][0]);
		close(exec->pipe_fd[i][1]);
		exec->pipe_fd[i][0] = -1;
		exec->pipe_fd[i][1] = -1;
		i++;
	}
}

void	execution(t_minishell *minishell)
{
	int	i;

	i = 0;
	init_exec(minishell->env, minishell->root, &minishell->exec);
	minishell->exec.pid = ft_calloc(minishell->exec.cmdc, sizeof(int));
	if (!minishell->exec.pid)
		ft_fprintf(STDERR_FILENO, "Allocation pid array failed");
	pipes_creation(&minishell->exec);
	children_creation(minishell, minishell->exec.pid);
	pipes_close(&minishell->exec);
	while (i < minishell->exec.cmdc)
	{
		waitpid(minishell->exec.pid[i], &minishell->exit_code, 0);
		// if (WIFEXITED(minishell->exit_code))
		// 	printf("exited, status=%d\n", WEXITSTATUS(minishell->exit_code));	// gestion d'erreur a changer
		i++;
	}
	// free(minishell->exec.delete_me[0]);
	// free_tab(minishell->exec.delete_me);
}
