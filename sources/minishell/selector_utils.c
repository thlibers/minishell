/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 10:22:51 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/16 08:53:32 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	reset_save(t_minishell *minishell)
{
	if (minishell->exec.child.save[0] > 2 || minishell->exec.child.save[1] > 2)
	{
		if (minishell->exec.child.save[0] > 2)
		{
			dup2(minishell->exec.child.save[0], STDIN_FILENO);
			close(minishell->exec.child.save[0]);
			minishell->exec.child.save[0] = -1;
		}
		if (minishell->exec.child.save[1] > 2)
		{
			dup2(minishell->exec.child.save[1], STDOUT_FILENO);
			close(minishell->exec.child.save[1]);
			minishell->exec.child.save[1] = -1;
		}
	}
}
