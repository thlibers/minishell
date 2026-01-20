/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:36:31 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/20 17:37:12 by thlibers         ###   ########.fr       */
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

void	*sort_env(t_env **env)
{
	t_env *head;
	t_env *tmp;
	int		sort;

	head = *env;
	sort = 1;
	while (!sort)
	{
		sort = 1;
		*env = head;
		while (*env)
		{
			if (ft_strcmp((*env)->name, (*env)->next->name) < 0)
			{
				tmp = *env;
				*env = (*env)->next;
				(*env)->next = tmp;
				sort = 0;
			}	
		}
		if (sort)
			break;
	}
	*env = head;
	return (env);
}