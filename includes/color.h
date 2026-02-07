/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:47:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/29 17:49:54 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RESET "\001\e[0m\002"

// --- FOREGROUND COLORS ---
# define F_RED "\001\e[0;31m\002"
# define F_GREEN "\001\e[0;32m\002"
# define F_BLUE "\001\e[0;34m\002"
# define F_YELLOW "\001\e[0;33m\002"
# define F_PURPLE "\001\e[0;35m\002"

// --- STYLIZATION ---
# define S_BOLD "\e[1m"
# define S_UNDERLINE "\e[4m"
# define S_SLOW_BLINK "\e[5m"
# define S_FAST_BLINK "\e[6m"

#endif
