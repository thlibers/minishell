/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 10:22:51 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/06 10:24:29 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	reset_save(t_minishell *minishell)
{
	if (minishell->exec.save[0] > 2 || minishell->exec.save[1] > 2)
	{
		dup2(minishell->exec.save[0], 0);
		if (minishell->exec.save[0] > 2)
			(close(minishell->exec.save[0]), minishell->exec.save[0] = -1);
		dup2(minishell->exec.save[1], 1);
		if (minishell->exec.save[1] > 2)
			(close(minishell->exec.save[1]), minishell->exec.save[1] = -1);
	}
}
