/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/22 17:34:00 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Define pour les fonction de signal.h
# define _XOPEN_SOURCE 700
# define	MSH_HIST  "msh_history"

# include "mylibft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char			*commad;
	char			**argument;
	char			*next_operator;
	struct s_token	*token_next;
}	t_token;

// typedef	struct s_store
// {
// 	int				fd_history;
// } t_store;

typedef struct s_minishell
{
	t_env				*env;
	t_token				*token;
	int					fd_history;
	int					last_code;
	struct sigaction	sa;
}						t_minishell;

int						env(t_minishell minishell);
bool  init_signal(t_minishell *minishell);


/* ============= BULTIN ============= */

//ft_cd.c

//ft_echo.c

//ft_env.c
int	ft_env(t_env *env);

//ft_exit.c

//ft_export.c
void					*sort_env(t_env **env);

//ft_pwd.c

//ft_unset.c


/* ============= MINISHELL ============= */

bool					init_minishell(t_minishell *minishell, char **envp);
bool					init_signal(t_minishell *minishell);


/* ============= PARSING ============= */

// env_vars.c
char					**env_spliter(char *vars);
bool					init_env(t_env **env, char **envp);
char					*ft_getenv(t_env *env, char *to_find);

t_token					*prompt(t_minishell minishell);
char					*ft_getenv(t_env *env, char *to_find);


/* ============= UTILS ============= */

void					env_clean(t_env *env, char **tab);
t_env					*env_cpy(t_env *env);

// env_utils.c
t_env					*new_env_node(void *name, void *content);
void 					*add_env_back(t_env **head, t_env *node);
void					swap_env_value(t_env **env);

// history.c
int						init_history(t_minishell *minishell);
int						add_to_history(int fd, char *line);

#endif
