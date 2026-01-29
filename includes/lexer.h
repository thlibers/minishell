/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:55:58 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 15:52:18 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
#endif

typedef enum e_data_type
{
	T_RED_IN = 1,
	T_RED_IN_APP = 2,
	T_RED_OUT,
	T_RED_OUT_APP,
	T_PIPE,
	T_HEREDOC
}						t_data_type;

typedef enum e_node_type
{
	T_WORD = 1,
}						t_node_type;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	int					arg_count;
}						t_command;

typedef struct s_token
{
	t_command			*comm_args;
	enum e_data_type	type;
	struct s_token		*next;
}						t_token;

// split_tokens.c

char					**ft_splitnoquote(char *s, char c);
void					clear_token(t_token **head);
