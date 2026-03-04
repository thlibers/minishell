/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/04 15:27:40 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number)
{
	init_child(exec, child_number, 0);
	if (exec->argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->exit_code = 1;
	}
	else if (exec->argc > 0 && !ft_strisdigit(exec->cmd[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			exec->cmd[1]);
		minishell->exit_code = 2;
	}
	else if (!exec->cmd[1])
		minishell->exit_code = 0;
	else
		minishell->exit_code = ft_atoi(exec->cmd[1]) % 256;
	child_clear(minishell);
	printf ("exit\n");
	exit(minishell->exit_code);
}
