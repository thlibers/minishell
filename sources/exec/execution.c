/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:08 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/11 16:14:54 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	pipes_creation(t_exec *exec)
{
	int	i;

	i = 0;
	exec->pipe_fd = ft_calloc(exec->cmdc, sizeof(int *));
	if (!exec->pipe_fd)
	{
		ft_fprintf(STDERR_FILENO, ENOENOMEM);
		return ;
	}
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
		minishell->exec.cmd = ast_to_arr(&minishell->exec, &tmp);
		if (minishell->exec.cmd)
		{
			arg_count(&minishell->exec);
			if (!selector(minishell, i))
			{
				pid[i] = fork();
				if (pid[i] == -1)
					ft_fprintf(STDERR_FILENO, ECRFORK);
				if (pid[i] == 0)
					child_process(minishell, i);
			}
			ptr_free_tab(&minishell->exec.cmd);
			close_file(&minishell->exec, tmp);
		}
		if (minishell->exec.infile_fd > 2)
			(close(minishell->exec.infile_fd), minishell->exec.infile_fd = -1);
		if (minishell->exec.outfile_fd > 2)
			(close(minishell->exec.outfile_fd), minishell->exec.outfile_fd = -1);
		i++;
		tmp = tmp->leaf_right;
	}
}

static void	execution_step(t_minishell *minishell)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (i < minishell->exec.cmdc)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sigint_exec);
		waitpid(minishell->pid[i], &code, 0);
		if (WIFSIGNALED(code))
			minishell->exit_code = 128 + WTERMSIG(code);
		else if (WIFEXITED(code))
			minishell->exit_code = WEXITSTATUS(code);
		else if (WIFSTOPPED(code))
			minishell->exit_code = WSTOPSIG(code);
		i++;
		init_signal();
	}
}

void	execution(t_minishell *minishell)
{
	if (!init_exec(minishell->env, minishell->ast, &minishell->exec, minishell))
		return ;
	minishell->pid = ft_calloc(minishell->exec.cmdc, sizeof(int));
	if (!minishell->pid)
	{
		ft_fprintf(STDERR_FILENO, ENOENOMEM);
		return ;
	}
	pipes_creation(&minishell->exec);
	children_creation(minishell, minishell->pid);
	pipes_close(&minishell->exec);
	execution_step(minishell);
	if (minishell->pid)
	{
		free(minishell->pid);
		minishell->pid = NULL;
	}
	ptr_free_tab(&minishell->exec.env);
}
