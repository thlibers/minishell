/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:02:55 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/25 17:07:47 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	selector(t_minishell *minishell, char *command)
{
	if (strcmp(command, "exit") == 0)
		ft_exit(minishell, NULL);
	//	else if (strcmp(command, "cd"))
	//		;
}
