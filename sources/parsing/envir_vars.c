/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 15:50:41 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char  **spliter_once(char *vars)
{
	int	  i;
	char **tab;
	char *pos;

	i = 0;
	tab = malloc(sizeof(char *) * (2 + 1));
	if (!tab)
		return (NULL);
	pos = strchr(vars, '=');
	if (!pos)
		return (NULL);
	tab[0] = calloc(pos - vars + 1, sizeof(char));
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	i = 0;
	tab[1] = calloc(strlen(vars) - (size_t)(pos - vars), sizeof(char));
	while (pos[1+i])
	{
		tab[1][i] = pos[1+i];
		i++;
	}
	tab[2] = NULL;
	return (tab);
}

static void  ev_add_back(t_ev **head, t_ev *node)
{
	t_ev  *cp;

	cp = *head;
	while (cp->next)
		cp = cp->next;
	cp->next = node;
}

// TODO : FREE
bool	  init_ev(t_ev **ev, char **envp)
{
	char  **tab;
	t_ev	*cp;
	t_ev	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		tab = spliter_once(envp[i]);
		if (!tab)
			return (ev_clean(head, NULL), false);
		cp = calloc(1, sizeof(t_ev));
		if (!cp)
			return (ev_clean(head, tab), false);
		cp->name = strdup(tab[0]);
		cp->value = strdup(tab[1]);
		cp->next = NULL;
		if (!head)
			head = cp;
		else 
			ev_add_back(&head, cp);
		ev_clean(NULL, tab);
		i++;
	}
	*ev = head;
	return (true);
}
