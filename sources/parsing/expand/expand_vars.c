/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:03:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/23 13:58:30 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	get_location_vars_name_end(t_tok **token, int i)
{
	int	y;

	y = i + 1;
	while ((*token)->str[y] && (ft_isalnum((*token)->str[y]) == true
			|| (*token)->str[y] == '_'))
		y++;
	return (y);
}

static bool	init_replace_var(t_expand *expand, t_env *env, t_tok **token)
{
	expand->last_char = get_location_vars_name_end(token, *(expand->first_char));
	expand->expanded = malloc(sizeof(char) * expand->last_char - *(expand->first_char));
	if (!expand->expanded)
		return (false);
	ft_strlcpy(expand->expanded, &(*token)->str[*(expand->first_char) + 1], expand->last_char
			- *(expand->first_char));
	expand->arg = malloc(ft_strlen((*token)->str) - expand->last_char + 1);
	if (!expand->arg)
		return (false);
	ft_strlcpy(expand->arg, &(*token)->str[expand->last_char], ft_strlen((*token)->str)
			- expand->last_char + 1);
	expand->env_value = ft_getenv(env, expand->expanded);
	return (true);
}

bool	replace_var(t_tok **token, t_env *env, int *i)
{
	t_expand  expand;

	expand.first_char = i;
	init_replace_var(&expand, env, token);
	if (!expand.expanded || !expand.arg)
	{
		if (expand.expanded)
			free(expand.expanded);
		else if (expand.arg)
			free(expand.arg);
		return (false);
	}
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) -
							(expand.last_char - *i) + ft_strlen(expand.env_value) + 1); // Invalid read 1
	if (!(*token)->str)
		return (free(expand.arg), free(expand.expanded), false);
	ft_strlcpy(&(*token)->str[*i], expand.env_value, ft_strlen(expand.env_value) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, expand.arg);
	free(expand.expanded);
	free(expand.arg);
	if (!(*token)->str)
		return (false);
	return (true);
}

void	ft_tilde(t_env *env, t_tok **token, int i)
{
	char	*env_value;
	char	*arg;
	int		y;

	y = i + 1;
	env_value = ft_getenv(env, "HOME");
	arg = malloc(ft_strlen((*token)->str) - y + 1);
	ft_strlcpy(arg, &(*token)->str[y], ft_strlen((*token)->str) - y + 1);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i)
			+ ft_strlen(env_value) + 1);
	ft_strlcpy(&(*token)->str[i], env_value, ft_strlen(env_value) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
}

void	ft_questionmark(t_minishell *minishell, t_tok **token, int i)
{
	char	*arg;
	int		y;

	y = i + 1;
	arg = malloc(ft_strlen((*token)->str) - y + 1);
	ft_strlcpy(arg, &(*token)->str[y + 1], ft_strlen((*token)->str) - y + 1);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i)
			+ ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	ft_strlcpy(&(*token)->str[i], ft_itoa(minishell->exit_code),
		ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
}
