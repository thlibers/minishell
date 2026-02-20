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

static void	remove_quotes(char **str)
{
	int	first_quote;
	int	last_quote;
	int	quote_type;
	int	len;
	int	i;

	first_quote = -1;
	last_quote = -1;
	quote_type = IN_RESET;
	len = ft_strlen(*str);
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
		else if (quote_type && ((*str)[i] == '\'' || (*str)[i] == '\"'))
		{
			first_quote = i;
			ft_strlcpy(&(*str)[last_quote], &(*str)[last_quote + 1], len - 1);
			ft_strlcpy(&(*str)[first_quote], &(*str)[first_quote + 1], len - 1);
			if (len - 2 == 0)
				*str = ft_realloc(*str, 1);
			// fix dans le cas ou l'arguments est juste "",
			// avant le fix on avait un segfault car fassait un malloc de 0
			else
				*str = ft_realloc(*str, len - 2);
			len -= 2;
			(*str)[len] = '\0';
			quote_type = IN_RESET;
		}
		i--;
	}
}

static void	expand_treatements(int *in_quote, t_minishell *minishell,
		t_env *env, t_tok **token)
{
	int	i;

	i = 0;
	while ((*token)->str[i])
	{
		if ((*token)->str[i] == '\'' && *in_quote == IN_RESET)
		{
			while ((*token)->str[i] && is_inquote(in_quote,
					(*token)->str[i]) == IN_SINGLE_QUOTE)
				i++;
			i++;
		}
		else
		{
			if ((*token)->str[i] == '~')
				ft_tilde(env, token, i);
			else if ((*token)->str[i] == '$')
			{
				if (!(*token)->str[i + 1] || (*token)->str[i + 1] == ' ')
				{
					i++; // Undefinded behavior $$
					continue ;
				}
				if ((*token)->str[i + 1] == '?')
					ft_questionmark(minishell, token, i);
				replace_var(token, env, &i);
			}
			else
				i++;
		}
	}
}

void	ft_expand(t_minishell *minishell, t_env *env, t_tok **token)
{
	int		in_quote;
	t_tok	*head;

	head = (*token);
	while (*token)
	{
		if ((*token)->type == T_WORD)
		{
			in_quote = IN_RESET;
			expand_treatements(&in_quote, minishell, env, token);
			remove_quotes(&(*token)->str);
		}
		*token = (*token)->next;
	}
	(*token) = head;
}

// Fonction a reorganiser
// $"$USER"$'$USER' expand deux fois au lieu d'une
//   - J'ai dig et ducoup c'est parce que on essaye de faire l'expand de $'
//   (qui n'est pas une variable d'env) donc la quote prend la place du $ ET
//   on incremente i. Donc on passe de ' a notre $ du deuxieme $USER, donc
//   pour le program il n'est pas dans des quote et il expand

//		Exemple :

// echo $PWD		-->		/home/.....
// echo '$PWD'		-->		$PWD
// echo "$PWD"		-->		/home/.....
// echo ~			-->		/home/.....
// echo "'$PWD'"	-->		'/home/...'
// echo '"$PWD"'	-->		"$PWD"

// echo $PWD+ss		-->		/home/.....+ss
// echo $"$PWD"$'$PWD' --> /home/....$PWD
