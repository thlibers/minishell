/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:35:02 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/05 13:51:17 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	env(t_minishell minishell)
{
	t_ev	*cp;

	cp = minishell.ev;
	while (cp)
	{
		printf("%s=%s\n", cp->name, cp->value);
		cp = cp->next;
	}
	return (0);
}
