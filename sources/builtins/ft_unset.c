/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:33 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/02 15:04:06 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	free_unset(t_minishell *minishell)
{
	if (minishell->env->next->name)
		free(minishell->env->next->name);
	if (minishell->env->next->value)
		free(minishell->env->next->value);
	if (minishell->env->next)
		free(minishell->env->next);
}

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
		minishell->env = head;
		while (minishell->env->next)
		{
			if (!ft_strcmp(exec->cmd[i], minishell->env->next->name))
			{
				tmp = minishell->env->next->next;
				free_unset(minishell);
				minishell->env->next = tmp;
				break ;
			}
			minishell->env = minishell->env->next;
		}
		i++;
	}
	minishell->exit_code = 0;
	minishell->env = head;
}
