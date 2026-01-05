/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/05 15:28:55 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char  **ev_tabs(void)
{
	char  ***tab;
	int	  i;

	i = 0;
	tab = malloc(sizeof(char **) * 4);
	if (!tab)
		return (NULL);
	free(tab);
	return (tab);
}

int	  init_ev(t_environment_vars **ev)
{
	t_environment_vars	*cp;
	int					i;

	cp = *ev;
	i = 0;

	while (i < 3)
	{
		cp = calloc(1, sizeof(t_environment_vars));
	//	cp->name = strdup("hhh");
		cp = cp->next;
		i++;
	}
	//(*ev)->name = strdup("PATH");
	//(*ev)->value = strdup(getenv("PATH"));
	//(*ev)->next->name = strdup("PWD");
	//(*ev)->next->value = strdup(getenv("PWD"));
	//(*ev)->next->next->name = strdup("USER");
	//(*ev)->next->next->value = strdup(getenv("USER"));
	return (1);
}
