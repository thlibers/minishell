/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:22:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/20 11:22:33 by nclavel          ###   ########.fr       */
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
			return (ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
		cpy->name = ft_strdup(env->name);
		if (!cpy->name)
			return (free(cpy), ft_fprintf(STDERR_FILENO, ENOENOMEM), NULL);
		cpy->value = ft_strdup(env->value);
		if (!cpy->value)
			return (free(cpy->name), free(cpy), ft_fprintf(STDERR_FILENO,
					ENOENOMEM), NULL);
		cpy->next = NULL;
		if (!head)
			head = cpy;
		else
			add_env_back(&head, cpy);
		env = env->next;
	}
	return (head);
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
