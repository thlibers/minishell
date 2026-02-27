/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/27 15:29:43 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number)
{
	int	exit_code;

	init_child(exec, child_number, 0);
	if (exec->argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->exit_code = 1;
		return ;
	}
	if (exec->argc > 0 && !ft_strisdigit(exec->cmd[0]))
	// A mettre au dessus
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			exec->cmd[1]);
		ft_clear(minishell);
		// DOUBLE FREE (suspission du ft_clear "sur a 100%" d'apres nclavel)
		exit(2);
	}
	else if (!exec->cmd[1])
	{
		exit_code = minishell->exit_code;
		ft_clear(minishell);
		exit(exit_code);
	}
	exit_code = ft_atoi(exec->cmd[1]) % 256;
	ft_clear(minishell);
	exit(exit_code);
}
