/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:59:09 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/04 11:59:12 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	child_half_clean(t_minishell **minishell)
{
	pipes_close(&(*minishell)->exec);
	if ((*minishell)->exec.infile_fd > 2)
		close((*minishell)->exec.infile_fd);
	if ((*minishell)->exec.outfile_fd > 2)
		close((*minishell)->exec.infile_fd);

}

void	child_full_clean(t_minishell **minishell)
{
	child_half_clean(minishell);
	if ((*minishell)->exec.env)
		free_tab((*minishell)->exec.env);
	if ((*minishell)->exec.cmd)
		free_tab((*minishell)->exec.cmd);
}
