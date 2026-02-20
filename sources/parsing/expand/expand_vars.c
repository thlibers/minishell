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
	int	y;

	y = i + 1;
	while ((*token)->str[y] && (ft_isalnum((*token)->str[y]) == true
			|| (*token)->str[y] == '_'))
		y++;
	return (y);
}

static bool	init_replace_var(t_expand *expand, t_env *env, t_tok **token)
{
	expand->y = get_location_vars_name_end(token, *(expand->i));
	expand->expanded = malloc(sizeof(char) * expand->y - *(expand->i));
	if (!expand->expanded)
		return (false);
	ft_strlcpy(expand->expanded, &(*token)->str[*(expand->i) + 1], expand->y
			- *(expand->i));
	expand->arg = malloc(ft_strlen((*token)->str) - expand->y + 1);
	if (!expand->arg)
		return (false);
	ft_strlcpy(expand->arg, &(*token)->str[expand->y], ft_strlen((*token)->str)
			- expand->y + 1);
	expand->env_value = ft_getenv(env, expand->expanded);
	return (true);
}

// Replace le $VAR en la valeur de la variable d'environement
bool	replace_var(t_tok **token, t_env *env, int *i)
{
	t_expand  expand;

	expand.i = i;
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
							(expand.y - *i) + ft_strlen(expand.env_value) + 1); // Invalid read 1
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

// Traitement de la tilde '~'
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

// Traitement du $? (donne le dernier exit code)
void	ft_questionmark(t_minishell *minishell, t_tok **token, int i)
{
	char	*arg;
	int		y;

	y = i + 1;
	arg = malloc(ft_strlen((*token)->str) - y + 1); // Un byte de trop ?
	ft_strlcpy(arg, &(*token)->str[y + 1], ft_strlen((*token)->str) - y + 1);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i)
			+ ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	ft_strlcpy(&(*token)->str[i], ft_itoa(minishell->exit_code),
		ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
}
