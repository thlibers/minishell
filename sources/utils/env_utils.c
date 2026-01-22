/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:36:31 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/22 16:29:40 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env	*ft_envnew(void *content)
{
	t_env	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->value = content;
	node->next = NULL;
	return (node);
}

static t_env	*ft_envlast(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (env == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	*ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return (NULL);
	if (*env == NULL)
	{
		*env = new;
		return (NULL);
	}
	tmp = ft_envlast(*env);
	tmp->next = new;
	return (*env);
}

t_env	*env_cpy(t_env *env)
{
	t_env 	*cpy;
	t_env	*head;

	head = NULL;
	while (env)
	{
		cpy = calloc(1 ,sizeof(t_env));
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

void	swap_env(t_env **env)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strdup((*env)->value);
	free((*env)->value);
	tmp2 = ft_strdup((*env)->name);
	free((*env)->name);
	(*env)->value = ft_strdup((*env)->next->value);
	free((*env)->next->value);
	(*env)->name = ft_strdup((*env)->next->name);
	free((*env)->next->name);
	(*env)->next->value = ft_strdup(tmp);
	free(tmp);
	(*env)->next->name = ft_strdup(tmp2);
	free(tmp2);
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
		while ((*env)->next)
		{
			if (ft_strcmp((*env)->name, (*env)->next->name) > 0)
			{
				swap_env(env);
				sort = 0;
			}
			*env = (*env)->next;
		}
	}
	*env = head;
	return (*env);
}
