/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 15:50:33 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ev_clean(t_ev *ev, char **tab)
{
	t_ev  *checkpoint;

	if (ev)
	{
		while(ev)
		{
			checkpoint = ev->next;
			free(ev->name);
			free(ev->value);
			free(ev);
			ev = checkpoint;
		}
	}
	if (tab)
	{
		free(tab[0]);
		free(tab[1]);
		free(tab);
	}
}
