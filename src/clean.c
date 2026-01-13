/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/05 14:14:32 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void  free_ev(t_ev *vars)
{
	t_ev	*save;
	
	while (vars->next)
	{
		save->next = vars->next;
		free(vars->name);
		free(vars->value);
		free(vars);
		vars = save->next;
	}
}
