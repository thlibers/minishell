/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:11:14 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/28 15:57:44 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	is_inquote(int *quote_state, char c)
{
	if (c == '"')
	{
		if (*quote_state == 2)
			*quote_state = 0;
		else if (*quote_state == 0)
			*quote_state = 2;
	}
	else if (c == '\'')
	{
		if (*quote_state == 1)
			*quote_state = 0;
		else if (*quote_state == 0)
			*quote_state = 1;
	}
}

static size_t	count_word(char *s, char sep)
{
	size_t	i;
	size_t	count;
	int		quote_state;

	i = 0;
	count = 0;
	quote_state = 0;
	while (s[i] && s[i] == sep)
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] != sep || quote_state != 0))
		{
			is_inquote(&quote_state, s[i]);
			i++;
		}
		if (s[i] == sep || (!s[i] && s[i - 1] != sep))
			count++;
		while (s[i] && s[i] == sep)
			i++;
	}
	return (count);
}

static char	*word_dup(const char *s, char sep)
{
	int		i;
	char	*str;
	int		quote_state;

	i = 0;
	quote_state = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] != sep || quote_state != 0))
	{
		is_inquote(&quote_state, s[i]);
		i++;
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	quote_state = 0;
	while (s[i] && (s[i] != sep || quote_state != 0))
	{
		str[i] = s[i];
		is_inquote(&quote_state, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

void	free_tab(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**ft_splitnoquote(char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	int		quote_state;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		tab[j] = word_dup(&(s[i]), c);
		if (!tab[j])
			return (free_tab(tab), NULL);
		j++;
		quote_state = 0;
		while (s[i] && (s[i] != c || quote_state != 0))
		{
			is_inquote(&quote_state, s[i]);
			i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

// int main()
// {
// 	size_t j;
// 	j = 0;
// 	// char str[] = "\"Hello \"Hello World ABC\"World ABC\" salut f \"wooooow bonjour\"";
// 	// char str[] = "\"Hello \" salut f \"wooooow bonjour\"";
// 	// char str[] = "Hello salut f \"wooooow bonjour\"";
// 	char str[] = "asdjd \"\'aklsdkjasd\'\"         ";
// 	char sep = ' ';
// 	char **s;

// 	s = ft_splitnoquote(str, sep);
// 	j = 0;
// 	while (s && s[j])
// 	{
// 		printf("%s\n", s[j]);
// 		j++;
// 	}

// 	if (s)
// 		free_tab(s);

// 	return(0);
// }
