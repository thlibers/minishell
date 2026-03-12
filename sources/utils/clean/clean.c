/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 19:27:19 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 16:08:30 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ptr_free_tab(char ***arr)
{
	int	i;

	i = 0;
	if (!*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	clean_heredoc_fd(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->heredoc.hd_fd_size)
	{
		if (exec->heredoc.hd_fd[i] > 2)
		{
			close(exec->heredoc.hd_fd[i]);
			exec->heredoc.hd_fd[i] = -1;
		}
		i++;
	}
}
