/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:36:31 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/05 16:27:37 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_env	*new_env_node(void *name, void *content)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (ft_fprintf(STDERR_FILENO, "\e[0;31mFailed allocate memory\e[0m"), NULL);
	node->name = ft_strdup(name);
	if (node->name)
		return(free(node), ft_fprintf(STDERR_FILENO, "\e[0;31mFailed allocate memory\e[0m"), NULL);
	node->value = ft_strdup(content);
	if (node->value)
		return(free(node->name), free(node), ft_fprintf(STDERR_FILENO, "\e[0;31mFailed allocate memory\e[0m"), NULL);
	node->next = NULL;
	return (node);
}

void	*add_env_back(t_env **head, t_env *node)
{
	t_env	*cp;

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

bool	edit_env(t_env **env, char *name, char *new_val)
{
	t_env	*head;

	head = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->name, name) == 0)
		{
			if (ft_strcmp(name, "PWD") == 0)
			{
				edit_env(env, "OLDPWD", (*env)->value);
			}
			if ((*env)->value)
				free((*env)->value);
			(*env)->value = ft_strdup(new_val);
			break ;
		}
		*env = (*env)->next;
	}
	*env = head;
	return (true);
}

void	swap_env_value(t_env **env)
{
	char	*tmp;
	char	*tmp2;

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
				swap_env_value(env);
				sort = 0;
			}
			*env = (*env)->next;
		}
	}
	*env = head;
	return (*env);
}
