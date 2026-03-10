/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:18:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/09 11:03:13 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	redirection_choser(t_exec *exec, t_ast *ast)
{
	if (ast && ast->type == T_PIPE && ast->top && ast->top->type >= T_HERE_DOC)
		ast = ast->leaf_right;
	while (ast && (ast)->leaf_right && (ast)->type >= T_HERE_DOC)
	{
		if ((ast)->type == T_RED_IN)
		{
			if (!file_opener(exec, ast, 0, &open_infile))
				return (false);
		}
		else if ((ast)->type == T_RED_OUT)
		{
			if (!file_opener(exec, ast, 1, &open_outfile))
				return (false);
		}
		else if ((ast)->type == T_RED_OUT_APP)
		{
			if (!file_opener(exec, ast, 0, &open_outfile))
				return (false);
		}
		if ((ast)->leaf_right->type == T_WORD)
			break ;
		ast = (ast)->leaf_right;
	}
	return (true);
}

bool	child_heredoc(t_exec *exec, t_minishell *minishell)
{
	int pid;
	int code;

	pid = fork();
	if (pid == 0)
		here_doc(exec, minishell);
	else
	{
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

int	init_exec(t_env *env, t_ast *ast, t_exec *exec, t_minishell *minishell)
{
	t_ast	*save;

	exec->cmdc = cmd_count(ast);
	exec->env = convert_env(env);
	save = minishell->ast;
	while (save)
	{
		if (save->type == T_HERE_DOC)
		{
			signal(SIGINT, handler_sigint_exec);
			save = save->leaf_right;
			exec->limiter = ft_strdup(save->leaf_left->data);
			if (!heredoc_init(exec))
				return (1);
			if (child_heredoc(exec, minishell))
				return (ptr_free_tab(&minishell->exec.env), 0);
			if (!terminate_heredoc(exec))
				return (1);
			signal(SIGINT, handler_sigint);
		}
		save = save->leaf_right;
	}
	return (1);
}
