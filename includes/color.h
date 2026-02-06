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

# define RESET "\e[0m"

// --- FOREGROUND COLORS ---
# define F_RED "\e[0;31m"
# define F_GREEN "\e[0;32m"
# define F_BLUE "\e[0;34m"
# define F_YELLOW "\e[0;33m"
# define F_PURPLE "\e[0;35m"

// --- STYLIZATION ---
# define S_BOLD "\e[1m"
# define S_UNDERLINE "\e[4m"
# define S_SLOW_BLINK "\e[5m"
# define S_FAST_BLINK "\e[6m"

#endif
