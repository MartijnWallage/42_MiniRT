/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:04:37 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 11:46:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief Set pixel color in the given image at (x, y) coordinates.
/// @param image Pointer to mlx_image_t representing the image.
/// @param x The x-coordinate.
/// @param y The y-coordinate.
/// @param color 32-bit integer representing RGBA color.
void	ft_put_pixel(mlx_image_t *image, unsigned int x, \
	unsigned int y, int color)
{
	unsigned char	*pixel;

	if (image && x < image->width && y < image->height)
	{
		pixel = &image->pixels[(y * image->width + x) * sizeof(int)];
		*(pixel++) = (unsigned char)get_r(color);
		*(pixel++) = (unsigned char)get_g(color);
		*(pixel++) = (unsigned char)get_b(color);
		*(pixel++) = (unsigned char)get_a(color);
	}
}
