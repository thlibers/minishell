/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:08 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/02 12:14:06 by thlibers         ###   ########.fr       */
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

void	close_file(t_exec *exec, t_ast *curr_branch)
{
	if (curr_branch->type >= T_HERE_DOC && curr_branch->leaf_right
		&& curr_branch->leaf_right->type < T_HERE_DOC)
	{
		if (exec->infile_fd > 2 && curr_branch->type >= T_RED_IN)
		{
			close(exec->infile_fd);
			exec->infile_fd = 0;
		}
		if (exec->outfile_fd > 2 && (curr_branch->type == T_RED_OUT
				|| curr_branch->type == T_RED_OUT_APP))
		{
			close(exec->outfile_fd);
			exec->outfile_fd = 1;
		}
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
		minishell->exec.cmd = ast_to_arr(&minishell->exec, &minishell->ast);
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
		close_file(&minishell->exec, minishell->ast);
		minishell->ast = minishell->ast->leaf_right;
	}
	minishell->ast = tmp;
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
	init_exec(minishell->env, minishell->ast, &minishell->exec, minishell);
	minishell->pid = ft_calloc(minishell->exec.cmdc, sizeof(int));
	if (!minishell->pid)
		ft_fprintf(STDERR_FILENO, ENOENOMEM);
	pipes_creation(&minishell->exec);
	children_creation(minishell, minishell->pid);
	pipes_close(&minishell->exec);
	while (i < minishell->exec.cmdc)
	{
		waitpid(minishell->pid[i], &code, 0);
		if (WIFSIGNALED(code))
			minishell->exit_code = 128 + WTERMSIG(code);
		else if (WIFEXITED(code))
			minishell->exit_code = WEXITSTATUS(code);
		else if (WIFSTOPPED(code))
			minishell->exit_code = WSTOPSIG(code);
		i++;
	}
	free_tab(minishell->exec.env);
}
