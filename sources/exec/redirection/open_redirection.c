/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:29:42 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 15:37:57 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_infile(char *filename, int trunc, t_exec *exec)
{
	(void)trunc;
	if (!filename)
		return (0);
	if (exec->child.infile_fd > 2)
		(close(exec->child.infile_fd), exec->child.infile_fd = -1);
	exec->child.infile_fd = open(filename, O_RDONLY);
	if (exec->child.infile_fd < 0)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		exec->child.infile_fd = open("/dev/null", O_RDONLY);
	}
	return (exec->child.infile_fd);
}

int	open_outfile(char *filename, int trunc, t_exec *exec)
{
	if (!filename)
		return (0);
	if (exec->child.outfile_fd > 2)
		(close(exec->child.outfile_fd), exec->child.outfile_fd = -1);
	if (trunc)
		exec->child.outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		exec->child.outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->child.outfile_fd == -1)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		return (-1);
	}
	return (exec->child.outfile_fd);
}

bool	file_opener(t_exec *exec, t_ast *ast, int flag, int (*ptr)(char *, int,
			t_exec *))
{
	t_ast	*save;

	save = ast;
	ast = ast->leaf_right;
	ptr(ast->leaf_left->data, flag, exec);
	ast = save;
	if (exec->child.infile_fd < 0 || exec->child.outfile_fd < 0)
		return (false);
	return (true);
}
