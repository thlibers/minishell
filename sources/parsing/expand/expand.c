/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:46:00 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/27 11:50:32 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	single_quote_treatement(int *in_quote, t_tok **token, int *i)
{
	while ((*token)->str[*i] && is_inquote(in_quote,
			(*token)->str[*i]) == IN_SINGLE_QUOTE)
		(*i)++;
	(*i)++;
}

static bool	dollar_treatements(t_minishell *minishell, t_tok **token, int *i)
{
	if (!(*token)->str[*i + 1] || (*token)->str[*i + 1] == ' '
		|| (*token)->str[*i + 1] == '$')
	{
		(*i)++;
		return (false);
	}
	else if ((*token)->str[*i + 1] == '?')
		ft_questionmark(minishell, token, *i);
	else
		replace_var(token, minishell->env, &*i);
	return (true);
}

static void	expand_treatements(int *in_quote, t_minishell *minishell,
		t_env *env, t_tok **token)
{
	int	i;

	i = 0;
	while ((*token)->str[i])
	{
		if ((*token)->str[i] == '\'' && *in_quote == IN_RESET)
			single_quote_treatement(in_quote, token, &i);
		else
		{
			if ((*token)->str[i] == '~')
				ft_tilde(env, token, i);
			else if ((*token)->str[i] == '$')
			{
				if (!dollar_treatements(minishell, token, &i))
					continue ;
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
