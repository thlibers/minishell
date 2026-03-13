/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:21:19 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 16:08:00 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <unistd.h>

int	heredoc_init(t_exec *exec)
{
	exec->files.hd_fd[exec->files.hd_fd_size] = open(HEREDOC_F,
			O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (exec->files.hd_fd[exec->files.hd_fd_size] < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to open/create/erase tmp file");
		return (0);
	}
	return (1);
}

int	terminate_heredoc(t_exec *exec)
{
	close(exec->files.hd_fd[exec->files.hd_fd_size]);
	exec->files.hd_fd[exec->files.hd_fd_size] = open(HEREDOC_F, O_RDONLY);
	if (exec->files.hd_fd[exec->files.hd_fd_size] < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to reopen heredoc file for reading");
		return (0);
	}
	exec->files.hd_fd_size++;
	unlink(HEREDOC_F);
	return (1);
}
