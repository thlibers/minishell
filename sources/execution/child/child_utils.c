/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:22:39 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 17:24:41 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clean_pipe_fd(t_exec *exec, int child_number, int is_child)
{
	if (is_child && exec->pipe_fd[child_number - 1][0] > 2)
		(close(exec->pipe_fd[child_number - 1][0]), exec->pipe_fd[child_number
			- 1][0] = -1);
	if (is_child && exec->pipe_fd[child_number - 1][1] > 2)
		(close(exec->pipe_fd[child_number - 1][1]), exec->pipe_fd[child_number
			- 1][1] = -1);
}
