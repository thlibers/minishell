/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:18:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/25 15:32:31 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	open_infile(char *filename)
{
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
	return (fd);
}

static int	open_outfile(char *filename, int trunc)
{
	int	fd;

	if (!filename)
		return (0);
	if (trunc)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		ft_fprintf(STDERR_FILENO, filename);
	return (fd);
}

int	init_exec(t_env *env, t_ast *ast, t_exec *exec)
{
	int		i;
	t_ast	*save;

	exec->cmdc = cmd_count(ast);
	exec->env = convert_env(env);
	i = 0;
	while (ast)
	{
		if (ast->type == T_HERE_DOC)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->limiter = ast->leaf_left->data;
			if (here_doc(exec))
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_IN)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->infile_fd = open_infile(ast->leaf_left->data);
			if (exec->infile_fd == 0)
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_OUT)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->outfile_fd = open_outfile(ast->leaf_left->data, O_TRUNC);
			if (exec->outfile_fd == 0)
				return (0);
			ast = save;
		}
		else if (ast->type == T_RED_OUT_APP)
		{
			save = ast;
			ast = ast->leaf_right;
			exec->outfile_fd = open_outfile(ast->leaf_left->data, 0);
			if (exec->outfile_fd == 0)
				return (0);
			ast = save;
		}
		i++;
		ast = ast->leaf_right;
	}
	return (1);
}
