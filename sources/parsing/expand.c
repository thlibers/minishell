/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:46:00 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/06 17:00:56 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_expand(t_minishell *minshell)
{
	while (minishell->)
	{
		
		
	}
}

// echo $PWD		-->		/home/.....
// echo '$PWD'		-->		$PWD
// echo "$PWD"		-->		/home/.....
// echo ~			-->		/home/.....
// echo "'$PWD'"	-->		/home/.....
// echo '"$PWD"'	-->		"$PWD"