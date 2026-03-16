/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:29:42 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/13 17:42:51 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_infile(char *filename, int trunc, t_child *child, t_files *files)
{
	(void)trunc;
	if (!filename || !files)
		return (0);
	if (files->fd_arr[0] > 2)
		close(files->fd_arr[0]);
	files->fd_arr[0] = open(filename, O_RDONLY);
	if (errno == ENOENT || errno == EACCES)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		files->fd_arr[0] = open("/dev/null", O_RDONLY);
	}
	child->infile_fd = &files->fd_arr[0];
	return (*child->infile_fd);
}

int	open_outfile(char *filename, int trunc, t_child *child, t_files *files)
{
	if (!filename || !files)
		return (0);
	if (files->fd_arr[1] > 2)
		close(files->fd_arr[1]);
	if (trunc)
		files->fd_arr[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		files->fd_arr[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (files->fd_arr[1] < 0)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		return (-1);
	}
	child->outfile_fd = &files->fd_arr[1];
	return (*child->outfile_fd);
}

bool	file_opener(t_exec *exec, t_ast *ast, int flag, int (*ptr)(char *, int,
			t_child *, t_files *))
{
	ast = ast->leaf_right;
	if (!ptr(ast->leaf_left->data, flag, &exec->child, &exec->files))
		return (false);
	return (true);
}
