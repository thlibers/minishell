/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:04:48 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/13 13:05:58 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	child_save(t_exec *exec, int is_child)
{
	if (!is_child)
	{
		exec->child.save[0] = dup(STDIN_FILENO);
		exec->child.save[1] = dup(STDOUT_FILENO);
	}
}
