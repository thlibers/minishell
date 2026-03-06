/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:18:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/04 17:03:15 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	open_infile(char *filename, int trunc, t_exec *exec)
{
	(void)trunc;
	if (!filename)
		return (0);
	exec->infile_fd = open(filename, O_RDONLY);
	if (exec->infile_fd < 0)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		exec->infile_fd = open("/dev/null", O_RDONLY);
	}
	return (exec->infile_fd);
}

static int	open_outfile(char *filename, int trunc, t_exec *exec)
{
	if (!filename)
		return (0);
	if (trunc)
		exec->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		exec->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->outfile_fd == -1)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		return (-1);
	}
	return (exec->outfile_fd);
}

bool	file_opener(t_exec *exec, t_ast *ast, int flag, int (*ptr)(char *, int,
			t_exec *))
{
	t_ast	*save;

	save = ast;
	ast = ast->leaf_right;
	ptr(ast->leaf_left->data, flag, exec);
	ast = save;
	if (exec->infile_fd < 0 || exec->outfile_fd < 0)
		return (false);
	return (true);
}

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

int	init_exec(t_env *env, t_ast *ast, t_exec *exec, t_minishell *minishell)
{
	t_ast	*save;

	exec->cmdc = cmd_count(ast);
	exec->env = convert_env(env);
	while (ast)
	{
		if (ast->type == T_HERE_DOC)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->limiter = ast->leaf_left->data;
			if (here_doc(exec, minishell))
				return (0);
			ast = save;
		}
		ast = ast->leaf_right;
	}
	return (1);
}

/*
int	init_exec(t_env *env, t_ast *ast, t_exec *exec, t_minishell *minishell)
{
	t_ast	*save;

	exec->cmdc = cmd_count(ast);
	exec->env = convert_env(env);
	while (ast)
	{
		if (ast->type == T_HERE_DOC)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->limiter = ast->leaf_left->data;
			if (here_doc(exec, minishell))
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_IN)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->infile_fd = open_infile(ast->leaf_left->data);
			if (exec->infile_fd < 0)
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_OUT)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->outfile_fd = open_outfile(ast->leaf_left->data, O_TRUNC);
			if (exec->outfile_fd < 0)
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_OUT_APP)
		{
			save = ast;
			ast = ast->leaf_right;
			if (!file_opener(exec, *ast, 0, &open_outfile))
				return (false);
			ast = save;
		}
		ast = ast->leaf_right;
	}
	return (1);
}
 */
