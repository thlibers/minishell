/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:33:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/05 20:35:08 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	ft_echo_nline(t_exec *exec, int *i)
{
	while (exec->cmd[*i][0] == '-' && exec->cmd[*i][1] == 'n')
		(*i)++;
	if (exec->cmd[*i - 1][0] == '-' && exec->cmd[*i - 1][1] == 'n')
		return (false);
	return (true);
}

int	ft_echo(t_minishell *minishell, t_exec *exec, int child_number)
{
	bool	new_line;
	int		i;

	i = 1;
	init_child(exec, child_number, 0);
	new_line = true;
	if (exec->argc == 0)
		return (ft_putchar_fd('\n', 1), 0);
	new_line = ft_echo_nline(exec, &i);
	while (exec->cmd[i])
	{
		if (i >= 1)
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
