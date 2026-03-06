/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/06 06:09:59 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number)
{
	int	exit_code;

	init_child(exec, child_number, 0);
	if (exec->argc > 0 && !ft_strisdigit(exec->cmd[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			exec->cmd[1]);
		full_clean(minishell);
		exit(2);
	}
	if (exec->argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->exit_code = 1;
		return ;
	}
	if (!exec->cmd[1])
		exit_code = minishell->exit_code;
	else
		exit_code = ft_atoi(exec->cmd[1]) % 256;
	full_clean(minishell);
	exit(exit_code);
}
