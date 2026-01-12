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

char  **spliter_once(char *vars)
{
	int	  i;
	char **tab;
	char *pos;

	i = 0;
	tab = malloc(sizeof(char) * (2 + 1));
	if (!tab)
		return (NULL);
	pos = strchr(vars, '=');
	if (!pos)
		return (NULL);
	tab[0] = calloc(pos - vars, sizeof(char));
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	i = 0;
	tab[1] = calloc(strlen(vars), sizeof(char));
	while (pos[1+i])
	{
		tab[1][i] = pos[1+i];
		i++;
	}
	tab[2] = NULL;
	return (tab);
}

void  *envp_to_linked(t_environment_vars **ev, char **envp)
{
	t_environment_vars	*cp;
	char				**tab;
	int					i;

	i = 0;
	cp = *ev;
	while (envp[i])
	{
		tab = spliter_once(envp[i]);
		if (!tab)
			;	
		cp = calloc(1, sizeof(t_environment_vars));
		if (!cp)
		{
			return (NULL);
		}
		cp->name = strdup(tab[0]);
		cp->value = strdup(tab[1]);
		cp = cp->next;
		i++;
		free(tab);
	}
	cp = NULL;
	return (ev);
}

int	  init_ev(t_environment_vars *ev, char **envp)
{
	t_environment_vars	*cp;
	int					i;

	i = 0;

	ev = envp_to_linked(&ev, envp);
	return (1);
}
