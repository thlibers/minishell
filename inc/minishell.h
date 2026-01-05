/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/04 21:45:46 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Define pour les fonction de signal.h
#define _XOPEN_SOURCE 700

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_environment_vars
{
	char  *name;
	char  *value;
	struct s_environment_vars *next;
} t_environment_vars;

typedef struct s_token
{
	char			**command;
	char			*next_operator;
	struct s_token	*token_next;
}	t_token;

typedef struct s_minishell
{
	t_environment_vars	*ev;
	t_token				token;
}	t_minishell;

t_token	*prompt(void);

#endif
