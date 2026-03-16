/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:06:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 14:42:24 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* --- CASUAL ---  */
# define ECRPIPE "\e[0;31mMinishell: Pipe creation failed\n\e[0m"
# define ECRFORK "\e[0;31mMinishell: Fork creation failed\n\e[0m"
# define EDUP2 "\e[0;31mMinishell: Failed to duplicated fds\n\e[0m"
# define ENOENOMEM "\e[0;31mMinishell: Failed allocate memory\n\e[0m"

/* --- CHECK --- */
# define EQUOTE "\e[0;31mMinishell: Unclosed quote\n\e[0m"
# define ESYNTAX "\e[0;31mMinishell: Syntax error\n\e[0m"
# define EUNHANDLE "\e[0;31mMinishell: unhandle operator detected\n\e[0m"

/* --- PARSING ---  */
# define ENOTFOUND "\e[0;31mMinishell: %s: No such file or directory\n\e[0m"
# define ECMDFOUND "\e[0;31mMinishell: %s: Command not found\n\e[0m"
# define ENOPERM "\e[0;31mMinishell: %s: Permission denied\n\e[0m"

/* --- BUILTIN ---  */
# define ECDARGC "Minishell: cd: too many arguments\n\e[0m"

/* --- EXEC ---  */
# define EEXECVE "\e[0;31mMinishell: Failed to execute \"%s\"\n\e[0m"

#endif // !ERROR_H
