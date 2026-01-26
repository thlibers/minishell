/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/26 15:37:44 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env	*env_cpy(t_env *env)
{
	t_env	*cpy;
	t_env	*head;

	head = NULL;
	while (env)
	{
		cpy = calloc(1, sizeof(t_env));
		if (!cpy)
			return (NULL);
		cpy->name = ft_strdup(env->name);
		cpy->value = ft_strdup(env->value);
		cpy->next = NULL;
		if (!head)
			head = cpy;
		else
			env_add_back(&head, cpy);
		env = env->next;
	}
	return (head);
}

void	*sort_env(t_env **env)
{
	t_env	*head;
	int		sort;

	head = *env;
	sort = 0;
	while (!sort)
	{
		sort = 1;
		*env = head;
		if (ft_strcmp((*env)->name, "_") == 0)
		{
			env_add_back(&head, env);
			continue ;
		}
		while ((*env)->next)
		{
			if (ft_strcmp((*env)->name, (*env)->next->name) > 0)
			{
				swap_env_value(env);
				sort = 0;
			}
			*env = (*env)->next;
		}
	}
	*env = head;
	return (*env);
}

// Manque :
//	-Check caracteres valides

int	ft_export_arg(t_minishell *minishell, char *str)
{
	t_env	*head;
	char	**tab;
	int		status;

	head = minishell->env;
	tab = env_spliter(str);
	if (!tab)
		return (1);
	status = 0;
	while (minishell->env && status == 0)
	{
		if (strcmp(minishell->env->name, tab[0]))
		{
			if (minishell->env->value)
				free(minishell->env->value);
			minishell->env->value = ft_strdup(tab[1]);
			status = 1;
		}
		minishell->env = minishell->env->next;
	}
	if (status == 0)
		add_env_back(minishell->env, env_new_node(tab[0], tab[1]));
	minishell->env = head;
	return (0);
}

void	ft_export(t_minishell *minishell)
{
	t_env	*cpy;

	cpy = env_cpy(minishell->env);
	sort_env(cpy);
	while (minishell->env->next)
	{
		printf("export %s=%s\n", cpy->name, cpy->value);
		minishell->env->next;
	}
}
