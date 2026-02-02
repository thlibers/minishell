/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/02 14:43:35 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**env_spliter(char *vars)
{
	int		i;
	char	**tab;
	char	*pos;

	i = 0;
	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (NULL);
	pos = ft_strchr(vars, '=');
	if (!pos)
		return (tab[0] = ft_strdup(vars), tab[1] = NULL, tab);
	tab[0] = ft_calloc(pos - vars + 1, sizeof(char));
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	i = 0;
	tab[1] = ft_calloc(strlen(vars) - (size_t)(pos - vars), sizeof(char));
	while (pos[1 + i])
	{
		tab[1][i] = pos[1 + i];
		i++;
	}
	return (tab[2] = NULL, tab);
}

bool	init_env(t_env **env, char **envp)
{
	char	**tab;
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
			add_env_back(&head, cp);
		env_clean(NULL, tab);
		i++;
	}
	*env = head;
	return (true);
}

char	*ft_getenv(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strcmp(env->name, to_find) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
