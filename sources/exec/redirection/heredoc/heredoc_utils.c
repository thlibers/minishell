/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:21:19 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/09 17:21:24 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	heredoc_init(t_exec *exec)
{
	if (exec->infile_fd > 2)
		close(exec->infile_fd);
	exec->infile_fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (exec->infile_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to open/create/erase tmp file");
		return (0);
	}
	return (1);
}

int	terminate_heredoc(t_exec *exec)
{
	close(exec->infile_fd);
	exec->infile_fd = open(HEREDOC_F, O_RDONLY);
	if (exec->infile_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to reopen heredoc file for reading");
		return (0);
	}
	return (1);
}
