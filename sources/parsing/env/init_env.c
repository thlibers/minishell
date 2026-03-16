/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 08:51:30 by nclavel          ###   ########.fr       */
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
		return (ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
	pos = ft_strchr(vars, '=');
	if (!pos)
		return (tab[0] = ft_strdup(vars), tab);
	tab[0] = ft_calloc(pos - vars + 1, sizeof(char));
	if (!tab[0])
		return (free(tab), ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
	while (i < pos - vars)
	{
		tab[0][i] = vars[i];
		i++;
	}
	if (vars[i] == '\0')
		return (tab);
	tab[1] = ft_strdup(pos + 1);
	if (!tab[1])
		return (free(tab[0]), free(tab), ft_fprintf(2, ENOENOMEM), NULL);
	return (tab);
}

t_env	*create_env_var(char *name, char *value, char *equal_loc)
{
	t_env	*var;

	var = NULL;
	var = calloc(1, sizeof(t_env));
	if (!var)
		return (ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
	var->name = ft_strdup(name);
	if (!var->name)
		return (free(var), ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
	var->value = ft_strdup(value);
	if (!equal_loc)
		var->equal = false;
	else
		var->equal = true;
	var->next = NULL;
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
			return (ptr_env_clean(&head, NULL), false);
		var = create_env_var(tab[0], tab[1], ft_strchr(envp[i], '='));
		if (!var)
			return (ptr_env_clean(&head, tab), NULL);
		if (!head)
			head = var;
		else
			add_env_back(&head, var);
		ptr_env_clean(NULL, tab);
		i++;
	}
	*env = head;
	return (true);
}
