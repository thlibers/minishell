/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:02:04 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/30 10:07:05 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_env(t_minishell *minishell)
{
	t_env	*cp;
	char	*tmp;

	tmp = NULL;
	cp = minishell->env;
	while (cp)
	{
		if (!ft_strcmp(cp->name, "_"))
			tmp = cp->value;
		else if (cp->value)
			printf("%s=%s\n", cp->name, cp->value);
		cp = cp->next;
	}
	if (tmp)
		printf("_=%s\n", tmp);
	minishell->exit_code = 0;
	return (0);
}
