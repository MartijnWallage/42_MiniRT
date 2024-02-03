/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:06:49 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:50 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* Get the red channel by moving 3 bytes to the right and masking 
	out the first byte. */
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

/* Get the green channel by moving 2 bytes to the right and masking 
	out the first byte. */
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

/* Get the blue channel by moving 1 bytes to the right and masking 
	out the first byte. */
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

/* Get the alpha channel by moving 0 bytes to the right and mask out 
	the first byte. */
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}
