/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:27 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 10:36:38 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_exit(t_minishell *minishell, t_command *command)
{
	int	exit_code;

	if (command->arg_count > 1)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		minishell->exit_code = 1;
		return ;
	}
	if (command->arg_count > 0 && !ft_strisdigit(command->arguments[0]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required",
			command->arguments[0]);
		ft_clear(minishell);			// DOUBLE FREE (suspission du ft_clear "sur a 100%" d'apres nclavel)
		exit(2);						
	}
	else if (!command->arguments[0])
	{
		exit_code = minishell->exit_code;
		ft_clear(minishell);
		exit(exit_code);
	}
	exit_code = ft_atoi(command->arguments[0]) % 256;
	ft_clear(minishell);
	exit(exit_code);
}
