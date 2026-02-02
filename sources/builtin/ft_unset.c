/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:33 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/02 12:59:12 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_unset(t_minishell *minishell, char *arg)
{
	while (minishell->env->next)
	{
		if (!ft_strcmp(arg, minishell->env->next->name))
		{
			free(minishell->env->next->name);
			free(minishell->env->next->value);
			free(minishell->env->next);
			minishell->env->next = minishell->env->next->next;
			minishell->exit_code = 0;
		}
		else
			minishell->exit_code = 1;
		minishell->env = minishell->env->next;
	}
}

// Si unset + une variable qui n'existe pas, pas d'erreur,
// retourne un code de succès.