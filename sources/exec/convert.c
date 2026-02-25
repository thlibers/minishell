/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:20:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/24 14:26:48 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_ast_arr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		printf("%s\n", (*arr)[i]);
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
	arr = ft_calloc(2, sizeof(char *));
	while (*ast && (*ast)->type == T_HERE_DOC && (*ast)->leaf_left
		&& !(*ast)->top)
		*ast = (*ast)->leaf_right;
	while (*ast && (*ast)->top && ((*ast)->top->type >= T_HERE_DOC))
		(*ast) = (*ast)->leaf_right;
	if (*ast || !(*ast)->top || (*ast)->type == T_PIPE || (*ast)->type == T_WORD
		|| (*ast)->top->type != T_HERE_DOC)
	{
		save = *ast;
		*ast = (*ast)->leaf_left;
		while (*ast)
		{
			//      printf("%s\n", (*ast)->data);
			arr[i] = ft_strdup((*ast)->data);
			if (!arr[i])
				return (arr[i] = NULL, free_tab(arr), NULL);
			if (i > 0)
			{
				arr = realloc(arr, sizeof(char *) * (2 + i + 1));
				arr[2 + i] = NULL;
			}
			i++;
			*ast = (*ast)->leaf_left;
		}
		*ast = save;
	}
	return (arr);
}
