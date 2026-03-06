/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:20:35 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/06 10:06:10 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	init_ast_to_arr(t_ast **ast, char ***arr, t_exec *exec)
{
	*arr = ft_calloc(1, sizeof(char *));
	if (!*arr)
		return (ft_fprintf(2, ENOENOMEM), false);
	while (*ast && (*ast)->top && ((*ast)->top->type >= T_HERE_DOC))
		(*ast) = (*ast)->leaf_right;
	if (!redirection_choser(exec, *ast))
		return (ptr_free_tab(arr), *arr = NULL, false);
	return (true);
}

char	**ast_to_arr(t_exec *exec, t_ast **ast)
{
	char	**arr;
	t_ast	*save;
	int		i;

	i = 0;
	if (!init_ast_to_arr(ast, &arr, exec))
		return (NULL);
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
		*ast = save;
	}
	return (arr);
}

void	arg_count(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmd[i])
		i++;
	exec->argc = i - 1;
}
