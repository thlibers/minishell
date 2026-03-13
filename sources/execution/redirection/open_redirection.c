/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:29:42 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 16:19:38 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_infile(char *filename, int trunc, t_child *child)
{
	(void)trunc;
	if (!filename)
		return (0);
	if (child->infile_fd > 2)
		(close(child->infile_fd), child->infile_fd = -1);
	child->infile_fd = open(filename, O_RDONLY);
	if (child->infile_fd < 0)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		child->infile_fd = open("/dev/null", O_RDONLY);
	}
	return (child->infile_fd);
}

int	open_outfile(char *filename, int trunc, t_child *child)
{
	if (!filename)
		return (0);
	if (child->outfile_fd > 2)
		(close(child->outfile_fd), child->outfile_fd = -1);
	if (trunc)
		child->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		child->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (child->outfile_fd == -1)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		return (-1);
	}
	return (child->outfile_fd);
}

bool	file_opener(t_child *child, t_ast *ast, int flag, int (*ptr)(char *,
			int, t_child *))
{
	t_ast	*save;

	save = ast;
	ast = ast->leaf_right;
	ptr(ast->leaf_left->data, flag, child);
	ast = save;
	if (child->infile_fd < 0 || child->outfile_fd < 0)
		return (false);
	return (true);
}
