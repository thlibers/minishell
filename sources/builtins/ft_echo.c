/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:33:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/05 14:16:01 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_echo(t_command *com_arg)
{
	bool	new_line;
	int		i;

	i = 0;
	new_line = true;
	if (com_arg->arg_count == 0)
		return (ft_putchar_fd('\n', 1), 0);
	if (ft_strcmp(com_arg->arguments[0], "-n") == 0)
		// "echo $PWD"	donne le pwd (expand)
		new_line = false;
	while (com_arg->arguments[i])
	{
		if ((i == 0 && new_line) || i >= 1)
		{
			ft_putstr_fd(com_arg->arguments[i], 1);
			if ((i + 1) != com_arg->arg_count)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (new_line == true)
		ft_putchar_fd('\n', 1);
	return (0);
}
