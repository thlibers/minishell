/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:20:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/27 12:53:47 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_ast_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
}

char	**ast_to_arr(t_ast **ast)
{
	char	**arr;
	t_ast	*save;
	int		i;

	i = 0;
	arr = ft_calloc(1, sizeof(char *));

	while (*ast && (*ast)->top && ((*ast)->top->type >= T_HERE_DOC))
		(*ast) = (*ast)->leaf_right;
	if (*ast || !(*ast)->top || (*ast)->type == T_PIPE || (*ast)->type == T_WORD
		|| (*ast)->top->type != T_HERE_DOC)
	{
		save = *ast;
		*ast = (*ast)->leaf_left;
		while (*ast)
		{
			arr = ft_realloc(arr, sizeof(char *) * (i + 1));
			arr[i] = ft_strdup((*ast)->data);
			if (!arr[i])
				return (arr[i] = NULL, free_tab(arr), NULL);
			i++;
			*ast = (*ast)->leaf_left;
		}
		// printf("\n");
		*ast = save;
	}
	return (arr);
}

void	arg_count(t_exec *exec)
{
	int i;
	
	i = 0;
	while (exec->cmd[i])
		i++;
	exec->argc = i - 1;
}
