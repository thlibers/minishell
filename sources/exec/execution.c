/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:08 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/27 15:28:11 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	pipes_creation(t_exec *exec)
{
	int	i;

	i = 0;
	exec->pipe_fd = ft_calloc(exec->cmdc, sizeof(int *));
	if (!exec->pipe_fd)
		ft_fprintf(STDERR_FILENO, ENOENOMEM);
	while (i < exec->cmdc - 1)
	{
		if (pipe(exec->pipe_fd[i]) == -1)
			ft_fprintf(STDERR_FILENO, ECRPIPE);
		i++;
	}
}

static void	children_creation(t_minishell *minishell, pid_t *pid)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	tmp = minishell->ast;
	while (i < minishell->exec.cmdc)
	{
		minishell->exec.cmd = ast_to_arr(&tmp);
		arg_count(&minishell->exec);
		if (!selector(minishell, i))
		{
			pid[i] = fork();
			if (pid[i] == -1)
				ft_fprintf(STDERR_FILENO, ECRFORK);
			if (pid[i] == 0)
				child_process(minishell, i);
		}
		i++;
		free_ast_arr(&minishell->exec.cmd);
		tmp = tmp->leaf_right;
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
	int	code;

	i = 0;
	code = 0;
	init_exec(minishell->env, minishell->ast, &minishell->exec);
	minishell->pid = ft_calloc(minishell->exec.cmdc, sizeof(int));
	if (!minishell->pid)
		ft_fprintf(STDERR_FILENO, ENOENOMEM);
	pipes_creation(&minishell->exec);
	children_creation(minishell, minishell->pid);
	pipes_close(&minishell->exec);
	while (i < minishell->exec.cmdc)
	{
		waitpid(minishell->pid[i], &code, 0);
		if (WIFEXITED(code))
			minishell->exit_code = WEXITSTATUS(code);
		i++;
	}
	free_tab(minishell->exec.env);
}
