/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:03:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/13 11:04:01 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Tous est dans le nom, sert a avoir la position de la find du nom de notre
// vars
int	get_location_vars_name_end(t_tok **token, int i)
{
	int y;

	y = i + 1;
	while ((*token)->str[y]
		&& (ft_isalnum((*token)->str[y]) == true
		|| (*token)->str[y] == '_'))
			y++;
	return (y);
}

// Replace le $VAR en la valeur de la variable d'environement
bool	replace_var(t_tok **token, t_env *env, int *i)
{
	char	*expand;
	char	*env_value;
	char	*arg;
	int y;

	y = get_location_vars_name_end(token, *i);
	expand = malloc(sizeof(char) * y - *i);
	if (!expand)
		return (false);
	ft_strlcpy(expand, &(*token)->str[*i + 1], y - *i);
	arg = malloc(ft_strlen((*token)->str) - y + 1);
	if (!arg)
		return (free(expand), false);
	ft_strlcpy(arg, &(*token)->str[y], ft_strlen((*token)->str) - y + 1);
	env_value = ft_getenv(env, expand);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - *i) + ft_strlen(env_value) + 1);
	if (!(*token)->str)
		return (free(arg), free(expand), false);
	ft_strlcpy(&(*token)->str[*i], env_value, ft_strlen(env_value) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
	free(expand);
	free(arg);
	if (!(*token)->str)
		return (false);
	return (true);
}
