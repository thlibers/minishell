/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:33 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/26 14:32:57 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_unset(t_env *env, char *arg)
{
	while (env->next)
	{
		if (!ft_strcmp(arg, env->next->name))
		{
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = env->next->next;
		}
		env = env->next;
	}
}

// Si unset + une variable qui n'existe pas, pas d'erreur, retourne un code de succès.