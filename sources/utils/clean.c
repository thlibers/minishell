/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:13:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 10:43:33 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_clear(t_minishell *minishell)
{
	clear_token(&minishell->token);
	env_clean(minishell->env, NULL);
	close(minishell->fd_history);
}

void	clear_token(t_token **head)
{
	t_token	*save;
	int		i;

	while (*head)
	{
		i = 0;
		save = (*head)->next;
		if (head)
		{
			if ((*head)->comm_args)
			{
				if ((*head)->comm_args->arguments)
				{
					while ((*head)->comm_args->arguments[i])
						free((*head)->comm_args->arguments[i++]);
					free((*head)->comm_args->arguments);
				}
				if ((*head)->comm_args->command)
					free((*head)->comm_args->command);
				free((*head)->comm_args);
			}
			free(*head);
		}
		*head = save;
	}
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

