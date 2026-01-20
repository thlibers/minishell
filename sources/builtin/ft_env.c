/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:35:02 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 17:34:47 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*cp;

	cp = env;
	while (cp)
	{
		ft_printf("%s=%s\n", cp->name, cp->value);
		cp = cp->next;
	}
	return (0);
}
