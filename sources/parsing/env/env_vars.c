/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/12 08:53:23 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// FAIRE UNE MEILLEURE GESTION D'ERREUR
// Permet de parser la variable d'environement recup en char *
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
		return (tab[0] = ft_strdup(vars), tab);
	tab[0] = ft_calloc(pos - vars + 1, sizeof(char));
	if (!tab[0])
		return (free(tab), NULL);
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	tab[0][i] = '\0';
	if (vars[i] == '\0')
		return (tab);
	tab[1] = ft_strdup(pos + 1);
	if (!tab[1])
		return (free(tab[0]), free(tab), NULL);
	return (tab);
}

t_env	*create_env_var(char *name, char *value, char *equal_loc)
{
	t_env	*var;

	var = NULL;
	var = calloc(1, sizeof(t_env));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	if (!equal_loc)
		var->equal = false;
	else
		var->equal = true;
	var->next = NULL;
	if (!var->name || !var->value)
		return (free(var), NULL);
	return (var);
}

bool	init_env(t_env **env, char **envp)
{
	char	**tab;
	t_env	*var;
	t_env	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		tab = env_spliter(envp[i]);
		if (!tab)
			return (env_clean(head, NULL), false);
		var = create_env_var(tab[0], tab[1], ft_strchr(envp[i], '='));
		if (!var)
			return (env_clean(head, tab), NULL);
		if (!head)
			head = var;
		else
			add_env_back(&head, var);
		env_clean(NULL, tab);
		i++;
	}
	*env = head;
	return (true);
}
