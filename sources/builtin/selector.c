/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:02:55 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 10:45:24 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	selector(t_minishell *minishell)
{
	if (strcmp(minishell->token->comm_args->command, "exit") == 0)
		ft_exit(minishell, minishell->token->comm_args);
	else if (strcmp(minishell->token->comm_args->command, "export") == 0)
		ft_export(minishell, minishell->token->comm_args);
	else if (strcmp(minishell->token->comm_args->command, "env") == 0)
		ft_env(minishell);
	// else if (strcmp(minishell->token->comm_args->command, "cd") == 0)
	// 	ft_cd(minishell);
	// else if (strcmp(command, "cd"))
	// 	ft_cd;
}
