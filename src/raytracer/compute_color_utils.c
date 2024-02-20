/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:05:03 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 14:06:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	scale_color(int c, t_real scale)
{
	t_real	rgb[3];

	rgb[0] = fmin((t_real)get_r(c) * scale, 255);
	rgb[1] = fmin((t_real)get_g(c) * scale, 255);
	rgb[2] = fmin((t_real)get_b(c) * scale, 255);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	alpha_shade(int c1, int c2, t_real alpha)
{
	t_real	rgb[3];

	rgb[0] = (1 - alpha) * (t_real)get_r(c1) + alpha * (t_real)get_r(c2);
	rgb[1] = (1 - alpha) * (t_real)get_g(c1) + alpha * (t_real)get_g(c2);
	rgb[2] = (1 - alpha) * (t_real)get_b(c1) + alpha * (t_real)get_b(c2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	mix_colors(int color1, int color2)
{
	t_real	rgb[3];

	rgb[0] = fmin((t_real)get_r(color1) / 255.0 * (t_real)get_r(color2), 255.0);
	rgb[1] = fmin((t_real)get_g(color1) / 255.0 * (t_real)get_g(color2), 255.0);
	rgb[2] = fmin((t_real)get_b(color1) / 255.0 * (t_real)get_b(color2), 255.0);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	add_colors(int c1, int c2)
{
	t_real	rgb[3];

	rgb[0] = ft_min(get_r(c1) + get_r(c2), 255);
	rgb[1] = ft_min(get_g(c1) + get_g(c2), 255);
	rgb[2] = ft_min(get_b(c1) + get_b(c2), 255);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}
