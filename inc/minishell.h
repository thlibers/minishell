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
#define	MSH_HIST  "~/.msh_history"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_environment_vars
{
	char  *name;
	char  *value;
	struct s_environment_vars *next;
} t_ev;

typedef struct s_token
{
	char			**command;
	char			*next_operator;
	struct s_token	*token_next;
}	t_token;

typedef	struct s_store
{
	int	fd_history;
}

typedef struct s_minishell
{
	t_ev	*ev;
	t_token				*token;
}	t_minishell;

t_token	*prompt(void);
bool		init_ev(t_ev **ev, char **envp);
int		env(t_minishell minishell);

#endif
