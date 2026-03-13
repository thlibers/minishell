/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:23:21 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 15:31:33 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	child_process(t_minishell *minishell, int child_number)
{
	char	*cmd_path;

	child_signal();
	init_child(&minishell->exec, child_number, 1);
	cmd_path = find_command_path(minishell, minishell->exec.child.cmd[0]);
	if (!cmd_path)
	{
		ft_fprintf(STDERR_FILENO, ECMDFOUND, minishell->exec.child.cmd[0]);
		full_clean(minishell);
		exit(127);
	};
	// half_clean(minishell);
	if (execve(cmd_path, minishell->exec.child.cmd, minishell->exec.env) == -1)
	{
		ft_fprintf(STDERR_FILENO, "execve failed\n");
		exit(126);
	}
}
