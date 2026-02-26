/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:22:25 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/25 14:04:10 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	print_error(char *message)
// {
// 	ft_putstr_fd("Error : ", 2);
// 	ft_putendl_fd(message, 2);
// 	exit(1);
// }

// void	free_array(char **array)
// {
// 	int	i;

// 	if (!array)
// 		return ;
// 	i = 0;
// 	while (array[i])
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// }

// static void	free_argsnpath(t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	while (i < exec->cmdc)
// 	{
// 		if (exec->delete_me[i])
// 		{
// 			free_tab(&exec->delete_me[i]);
// 			exec->delete_me[i] = NULL;
// 		}
// 		i++;
// 	}
// 	if (exec->delete_me)
// 		free(exec->delete_me);
// }

void	cleanup_pipe(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec)
		return ;
	if (exec->infile_fd > 2)
		(close(exec->infile_fd), exec->infile_fd = -1);
	if (exec->outfile_fd > 2)
		(close(exec->outfile_fd), exec->outfile_fd = -1);
	if (exec->limiter)
		free(exec->limiter);
	while (i < exec->cmdc)
	{
		if (exec->pipe_fd[i][0] > 2)
			(close(exec->pipe_fd[i][0]), exec->pipe_fd[i][0] = -1);
		if (exec->pipe_fd[i][1] > 2)
			(close(exec->pipe_fd[i][1]), exec->pipe_fd[i][1] = -1);
		i++;
	}
	if (exec->pipe_fd)
		free(exec->pipe_fd);
	if (exec->pid)
		free(exec->pid);
}
