/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:07:24 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/05 13:11:00 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	minishell_history(t_minishell *minishell)
{
	;
}

int	msh_add_history()
{
	;
}

bool  init_history(t_minishell *minishell)
{
	minishell->fd_history = open(MSH_HIST, O_WRONLY | O_CREAT | O_TRUNC, 00644);

}
