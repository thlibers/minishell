/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 13:08:24 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, char **args)
{
	int	exit_code;

	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->last_code = 1;
		return ;
	}
	if (!ft_strisdigit(args[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			args[1]);
		// ft_clean(minishell)
		exit(2);
	}
	else if (!args[1])
	{
		exit_code = minishell->last_code;
		// ft_clean(minishell)
		exit(exit_code);
	}
	exit_code = ft_atoi(args[1]) % 256;
	// ft_clean(minishell)
	exit(exit_code);
}
