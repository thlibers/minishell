/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:46:00 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/11 17:14:35 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	remove_quotes(char **str)
{
	int		i;
	int		len;
	int		first_quote;
	int		last_quote;
	int		quote_type;

	len = ft_strlen(*str);
	first_quote = -1;
	last_quote = -1;
	quote_type = IN_RESET;
	i = len - 1;
	while (i >= 0)
	{
		if ((*str)[i] == '\'' && quote_type == IN_RESET)
		{
			quote_type = IN_SINGLE_QUOTE;
			last_quote = i;
		}
		else if ((*str)[i] == '\"' && quote_type == IN_RESET)
		{
			quote_type = IN_DOUBLE_QUOTE;
			last_quote = i;
		}
		else if ((quote_type == IN_SINGLE_QUOTE && (*str)[i] == '\'') || (quote_type == IN_DOUBLE_QUOTE && (*str)[i] == '\"'))
		{
			first_quote = i;
			ft_strlcpy(&(*str)[last_quote], &(*str)[last_quote + 1], len - 1);
			ft_strlcpy(&(*str)[first_quote], &(*str)[first_quote + 1], len - 1);
			if (len - 2 == 0)
				*str = ft_realloc(*str, 1); // fix dans le cas ou l'arguments est juste "", avant le fix on avait un segfault car fassait un malloc de 0
			else 
				*str = ft_realloc(*str, len - 2);
			len -= 2;
			(*str)[len] = '\0';
			quote_type = IN_RESET;
		}
		i--;
	}
}

void	ft_tilde(t_env *env, t_tok **token, int i)
{
	char	*env_value;
	char	*arg;
	int y;

	y = i + 1;
	env_value = ft_getenv(env, "HOME");
	arg = malloc(ft_strlen((*token)->str) - y + 1);
	ft_strlcpy(arg, &(*token)->str[y], ft_strlen((*token)->str) - y + 1);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i) + ft_strlen(env_value) + 1);
	ft_strlcpy(&(*token)->str[i], env_value, ft_strlen(env_value) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
}

void	ft_questionmark(t_minishell *minishell, t_tok **token, int i)
{
	char	*arg;
	int y;

	y = i + 1;
	arg = malloc(ft_strlen((*token)->str) - y + 1);				// Un byte de trop ?
	ft_strlcpy(arg, &(*token)->str[y + 1], ft_strlen((*token)->str) - y + 1);
	(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i) + ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	ft_strlcpy(&(*token)->str[i], ft_itoa(minishell->exit_code), ft_strlen(ft_itoa(minishell->exit_code)) + 1);
	(*token)->str = ft_strfreejoin((*token)->str, arg);
}

void	ft_expand(t_minishell *minishell, t_env *env, t_tok **token)
{
	int		i;
	int		y;
	int		in_quote;
	char	*expand;
	char	*env_value;
	char	*arg;
	t_tok	*head;

	head = (*token);
	while (*token)
	{
		if ((*token)->type == T_WORD)
		{
			i = 0;
			in_quote = 0;
			while ((*token)->str[i])
			{
				if ((*token)->str[i] == '"' && in_quote == IN_RESET)
					in_quote = IN_DOUBLE_QUOTE;
				else if ((*token)->str[i] == '"' && in_quote == IN_DOUBLE_QUOTE)
					in_quote = IN_RESET;
				if ((*token)->str[i] == '\'' && in_quote == IN_RESET)
				{
					while ((*token)->str[i] && is_inquote(&in_quote,
							(*token)->str[i]) == IN_SINGLE_QUOTE)
						i++;
					i++;
				}
				else
				{
					if ((*token)->str[i] == '~')
					{
						ft_tilde(env, token, i);
						return ;
					}
					if ((*token)->str[i] == '$')
					{
						if ((*token)->str[i + 1] == '?')
						{
							ft_questionmark(minishell, token, i);
							return ;
						}
						else if (!(*token)->str[i + 1] || !ft_isalnum((*token)->str[i + 1]))
						{
							i++;
							continue ;
						}
						y = i + 1;
						while ((*token)->str[y]
							&& (ft_isalnum((*token)->str[y]) == true
								|| (*token)->str[y] == '_'))
							y++;
						expand = malloc(sizeof(char) * y - i);
						ft_strlcpy(expand, &(*token)->str[i + 1], y - i);
						arg = malloc(ft_strlen((*token)->str) - y + 1);
						ft_strlcpy(arg, &(*token)->str[y], ft_strlen((*token)->str) - y + 1);
						env_value = ft_getenv(env, expand);
						(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i) + ft_strlen(env_value) + 1);
						ft_strlcpy(&(*token)->str[i], env_value, ft_strlen(env_value) + 1);
						(*token)->str = ft_strfreejoin((*token)->str, arg);
						free(expand);
						free(arg);
					}
					else
						i++;
				}
			}
			remove_quotes(&(*token)->str);
		}
		*token = (*token)->next;
	}
	(*token) = head;
}

// Fonction a reorganiser
// $"$USER"$'$USER' expand deux fois au lieu d'une
//   - J'ai dig et ducoup c'est parce que on essaye de faire l'expand de $' (qui n'est pas une variable d'env) donc la quote prend la place du $ ET on incremente i. Donc on passe de ' a notre $ du deuxieme $USER, donc pour le program il n'est pas dans des quote et il expand

//		Exemple :

// echo $PWD		-->		/home/.....
// echo '$PWD'		-->		$PWD
// echo "$PWD"		-->		/home/.....
// echo ~			-->		/home/.....
// echo "'$PWD'"	-->		'/home/...'
// echo '"$PWD"'	-->		"$PWD"

// echo $PWD+ss		-->		/home/.....+ss
