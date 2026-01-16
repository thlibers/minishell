/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:35:02 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 15:45:10 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	env(t_minishell minishell)
{
	t_ev	*cp;

	cp = minishell.ev;
	while (cp)
	{
		ft_printf("%s=%s\n", cp->name, cp->value);
		cp = cp->next;
	}
	return (0);
}
