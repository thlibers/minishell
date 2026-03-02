/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:33 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/02 14:29:26 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_unset(t_minishell *minishell, t_exec *exec, int child_number)
{
	t_env	*tmp;
	t_env	*head;
	int		i;

	i = 1;
	head = minishell->env;
	init_child(exec, child_number, 0);
	while (exec->cmd[i])
	{
		while (minishell->env->next)
		{
			if (!ft_strcmp(exec->cmd[i], minishell->env->next->name))
			{
				tmp = minishell->env->next->next;
				free(minishell->env->next->name);
				free(minishell->env->next->value);
				free(minishell->env->next);
				minishell->env->next = tmp;
				minishell->exit_code = 0;
			}
			else
				minishell->exit_code = 1;
			minishell->env = minishell->env->next;
		}
		i++;
	}
	minishell->env = head;
}

// Si unset + une variable qui n'existe pas, pas d'erreur,
// retourne un code de succès.

// uset plusieurs variables en meme temps ?
