/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 09:03:10 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number)
{
	int	exit_code;

	(void)child_number;
	if (exec->child.argc > 0 && !ft_strisdigit(exec->child.cmd[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			exec->child.cmd[1]);
		clean_all(minishell);
		exit(2);
	}
	if (exec->child.argc > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->exit_code = 1;
		return ;
	}
	if (!exec->child.cmd[1])
		exit_code = minishell->exit_code;
	else
		exit_code = ft_atoi(exec->child.cmd[1]) % 256;
	clean_all(minishell);
	printf("exit\n");
	exit(exit_code);
}
