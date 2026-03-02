/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:06:53 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/24 14:07:38 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "includes/color.h"

/* --- CASUAL ---  */
# define ECRPIPE F_RED "Minishell: Pipe creation failed" RESET
# define ECRFORK F_RED "Minishell: Fork creation failed" RESET
# define EDUP2 F_RED "Minishell: Failed to duplicated fds" RESET
# define ENOENOMEM F_RED "Minishell: Failed allocate memory\n" RESET

/* --- CHECK --- */
# define EQUOTE F_RED "Minishell: Unclosed quote\n" RESET
# define ESYNTAX F_RED "Minishell: Syntax error\n" RESET
# define EUNHANDLE F_RED "Minishell: unhandle operator detected\n" RESET

/* --- PARSING ---  */
# define ENOTFOUND F_RED "Minishell: %s: No such file or directory\n" RESET
# define ECMDFOUND F_RED "Minishell: %s: Command not found\n" RESET
# define ENOPERM F_RED "Minishell: %s: Permission denied\n" RESET

# define ECDARGC F_RED "Minishell: cd: too many arguments\n" RESET

#endif // !ERROR_H
