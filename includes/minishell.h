/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/11 14:51:43 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/color.h"
# include "includes/prototypes.h"
# include "includes/structure.h"

# define _XOPEN_SOURCE 700
# define MSH_HIST "msh_history"

# define IN_RESET 0
# define IN_SINGLE_QUOTE 1
# define IN_DOUBLE_QUOTE 2

# include "color.h"
# include "mylibft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#endif
