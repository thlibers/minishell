/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 15:14:27 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void  ft_clear(t_minishell	*minishell)
{
	env_clean(minishell->env, NULL);
}

void	env_clean(t_env *env, char **tab)
{
	t_env	*checkpoint;

	if (env)
	{
		while (env)
		{
			checkpoint = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = checkpoint;
		}
	}
	if (tab)
	{
		free(tab[0]);
		free(tab[1]);
		free(tab);
	}
}
