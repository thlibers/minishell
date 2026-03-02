/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:33:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/02 15:17:56 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_echo(t_minishell *minishell, t_exec *exec, int child_number)
{
	bool	new_line;
	int		i;

	i = 1;
	init_child(exec, child_number, 0);
	new_line = true;
	if (exec->argc == 0)
		return (ft_putchar_fd('\n', 1), 0);
	if (ft_strcmp(exec->cmd[1], "-n") == 0)
		new_line = false;
	while (exec->cmd[i])
	{
		if ((i == 1 && new_line) || i >= 2)
		{
			ft_putstr_fd(exec->cmd[i], 1);
			if (i != exec->argc)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (new_line == true)
		ft_putchar_fd('\n', 1);
	minishell->exit_code = 0;
	return (0);
}
