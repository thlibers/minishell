/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:35:02 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/26 14:33:25 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*cp;
	char	*tmp;

	tmp = NULL;
	cp = env;
	while (cp)
	{
		if (!ft_strcmp(cp->name, "_"))
			tmp = cp->value;
		else
			printf("%s=%s\n", cp->name, cp->value);
		cp = cp->next;
	}
	if (tmp)
		printf("%s=%s\n", "_", tmp);
	return (0);
}
