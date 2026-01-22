/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:36:31 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/22 17:24:44 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env	*new_env_node(void *name, void *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->name = name;
	node->value = content;
	node->next = NULL;
	return (node);
}

void 	*add_env_back(t_env **head, t_env *node)
{
	t_env  *cp;

	if (!node)
		return (NULL);
	if (*head == NULL)
	{
		*head = node;
		return (*head);
	}
	cp = *head;
	while (cp->next)
		cp = cp->next;
	cp->next = node;
	return (*head);
}

void	swap_env_value(t_env **env)
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
