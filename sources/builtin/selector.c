/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:02:55 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 11:20:18 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	selector(t_minishell *minishell, char *command)
{
	if (strcmp(command, "exit") == 0)
		ft_exit(minishell, minishell->token->comm_args);
	else if (strcmp(command, "export") == 0)
		ft_export(minishell, minishell->token->comm_args);
	// else if (strcmp(command, "export"))
	// 	ft_export(minishell, );
	//	else if (strcmp(command, "cd"))
	//		ft_;
}
