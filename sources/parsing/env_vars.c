/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/22 14:54:18 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char  **env_spliter(char *vars)
{
	int	  i;
	char **tab;
	char *pos;

	i = 0;
	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (NULL);
	pos = ft_strchr(vars, '=');
	if (!pos)
		return (NULL);
	tab[0] = ft_calloc(pos - vars + 1, sizeof(char));
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	i = 0;
	tab[1] = ft_calloc(strlen(vars) - (size_t)(pos - vars), sizeof(char));
	while (pos[1+i])
	{
		tab[1][i] = pos[1 + i];
		i++;
	}
	tab[2] = NULL;
	return (tab);
}

void  env_add_back(t_env **head, t_env *node)
{
	t_env  *cp;

	cp = *head;
	while (cp->next)
		cp = cp->next;
	cp->next = node;
}

// TODO : FREE
bool	  init_env(t_env **env, char **envp)
{
	char  **tab;
	t_env	*cp;
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		tab = env_spliter(envp[i]);
		if (!tab)
			return (env_clean(head, NULL), false);
		cp = ft_calloc(1, sizeof(t_env));
		if (!cp)
			return (env_clean(head, tab), false);
		cp->name = strdup(tab[0]);
		cp->value = strdup(tab[1]);
		cp->next = NULL;
		if (!head)
			head = cp;
		else 
			env_add_back(&head, cp);
		env_clean(NULL, tab);
		i++;
	}
	*env = head;
	return (true);
}

char *ft_getenv(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strcmp(env->name, to_find))
		{
			return(env->value);
		}
	}
	return (NULL);
}