/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:18:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/13 15:50:26 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/structure.h"
#include "mylibft/libft.h"

static bool	child_heredoc(t_exec *exec, t_minishell *minishell)
{
	int	pid;
	int	code;

	pid = fork();
	if (pid == 0)
		here_doc(exec, minishell);
	else
	{
		if (minishell->exec.limiter)
			(free(minishell->exec.limiter), minishell->exec.limiter = NULL);
		waitpid(pid, &code, 0);
		if (WIFSIGNALED(code))
		{
			minishell->exit_code = 128 + WTERMSIG(code);
			return (false);
		}
		else if (WIFEXITED(code))
			minishell->exit_code = WEXITSTATUS(code);
	}
	return (true);
}

static int	heredoc_fd_init(t_minishell *minishell, t_ast *save)
{
	signal(SIGINT, handler_sigint_exec);
	save = save->leaf_right;
	minishell->exec.limiter = ft_strdup(save->leaf_left->data);
	if (!minishell->exec.limiter)
	{
		signal(SIGINT, handler_sigint);
		return (0);
	}
	if (!heredoc_init(&minishell->exec))
	{
		signal(SIGINT, handler_sigint);
		return (0);
	}
	if (!child_heredoc(&minishell->exec, minishell))
	{
		signal(SIGINT, handler_sigint);
		return (ptr_free_tab(&minishell->exec.env), 0);
	}
	if (!terminate_heredoc(&minishell->exec))
		return (signal(SIGINT, handler_sigint), 0);
	signal(SIGINT, handler_sigint);
	return (1);
}

int	init_exec(t_env *env, t_ast *ast, t_exec *exec, t_minishell *minishell)
{
	t_ast	*save;

	if (exec->child.infile_fd > 2)
		close(exec->child.infile_fd);
	if (exec->child.outfile_fd > 2)
		close(exec->child.outfile_fd);
	ft_memset(&minishell->exec, 0, sizeof(t_exec));
	ft_memset(&minishell->exec.files, 0, sizeof(t_files));
	exec->cmdc = cmd_count(ast);
	exec->env = convert_env(env);
	save = minishell->ast;
	while (save)
	{
		if (save->type == T_HERE_DOC)
		{
			if (!heredoc_fd_init(minishell, save))
				return (0);
		}
		save = save->leaf_right;
	}
	return (1);
}
