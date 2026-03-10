/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:06:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/06 06:59:28 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "includes/color.h"

/* --- CASUAL ---  */
# define ECRPIPE "\001\e[0;31m\002Minishell: Pipe creation failed\n\001\e[0m\002"
# define ECRFORK "\001\e[0;31m\002Minishell: Fork creation failed\n\001\e[0m\002"
# define EDUP2 "\001\e[0;31m\002Minishell: Failed to duplicated fds\n\001\e[0m\002"
# define ENOENOMEM "\001\e[0;31m\002Minishell: Failed allocate memory\n\001\e[0m\002"

/* --- CHECK --- */
# define EQUOTE "\001\e[0;31m\002Minishell: Unclosed quote\n\001\e[0m\002"
# define ESYNTAX "\001\e[0;31m\002Minishell: Syntax error\n\001\e[0m\002"
# define EUNHANDLE "\001\e[0;31m\002Minishell: unhandle operator detected\n\001\e[0m\002"

/* --- PARSING ---  */
# define ENOTFOUND "\001\e[0;31m\002Minishell: %s: No such file or directory\n\001\e[0m\002"
# define ECMDFOUND "\001\e[0;31m\002Minishell: %s: Command not found\n\001\e[0m\002"
# define ENOPERM "\001\e[0;31m\002Minishell: %s: Permission denied\n\001\e[0m\002"

# define ECDARGC "Minishell: cd: too many arguments\n\001\e[0m\002"

#endif // !ERROR_H
