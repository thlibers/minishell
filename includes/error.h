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

# define ENOTFOUND F_RED "Minishell: %s: No such file or directory\n" RESET
# define ENOENOMEM F_RED "Failed allocate memory\n" RESET
# define ENOPERM F_RED "Minishell: %s: Permission denied\n" RESET
#endif // !ERROR_H
