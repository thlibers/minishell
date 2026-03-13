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
#include "includes/structure.h"

int	open_infile(char *filename, int trunc, t_child *child, t_files *files)
{
	(void)trunc;
	if (!filename || !files)
		return (0);
	if (!files->fd_arr)
		files->fd_arr = ft_calloc(1, sizeof(t_files));
	else
		ft_hoelalloc(files->fd_arr, files->fd_size, files->fd_size + 1);
	files->fd_arr[files->fd_size] = open(filename, O_RDONLY);
	if (errno == ENOENT || errno == EACCES)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		files->fd_arr[files->fd_size] = open("/dev/null", O_RDONLY);
	}
	child->infile_fd = &files->fd_arr[files->fd_size];
	files->fd_size++;
	return (*child->infile_fd);
}

int	open_outfile(char *filename, int trunc, t_child *child, t_files *files)
{
	if (!filename || !files)
		return (0);
	if (!files->fd_arr)
		files->fd_arr = ft_calloc(1, sizeof(t_files));
	else
		ft_hoelalloc(files->fd_arr, files->fd_size, files->fd_size + 1);
	if (trunc)
		files->fd_arr[files->fd_size] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		files->fd_arr[files->fd_size] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (files->fd_arr[files->fd_size] < 0)
	{
		if (errno == ENOENT)
			ft_fprintf(STDERR_FILENO, ENOTFOUND, filename);
		else
			ft_fprintf(STDERR_FILENO, ENOPERM, filename);
		return (-1);
	}
	child->outfile_fd = &files->fd_arr[files->fd_size];
	files->fd_size++;
	return (*child->outfile_fd);
}

bool	file_opener(t_exec *exec, t_ast *ast, int flag, int (*ptr)(char *,
			int, t_child *, t_files *))
{
	t_ast	*save;

	save = ast;
	ast = ast->leaf_right;
	ast = save;
	if (!ptr(ast->leaf_left->data, flag, &exec->child, &exec->files))
		return (false);
	return (true);
}
