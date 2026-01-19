/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/19 15:13:51 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Define pour les fonction de signal.h
# define _XOPEN_SOURCE 700
# define	MSH_HIST  "~/.minishell_history"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <signal.h>
# include "mylibft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
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

// typedef	struct s_store
// {
// 	int				fd_history;
// } t_store;

typedef struct s_minishell
{
	t_ev			*ev;
	t_token			*token;
	int				fd_history;
	int				last_code;
	struct sigaction		sa;
}	t_minishell;



bool		init_ev(t_ev **ev, char **envp);
int		env(t_minishell minishell);

/* ============= PARSING ============= */

t_token	*prompt(t_minishell minishell);

/* ============= MINISHELL ============= */

bool  init_minishell(t_minishell *minishell, char **envp);

/* ============= HISTORY ============= */

int	init_history(t_minishell *minishell);
int	add_to_history(int fd, char *line);

/* ============= UTILS ============= */

void	ev_clean(t_ev *ev, char **tab);

#endif
