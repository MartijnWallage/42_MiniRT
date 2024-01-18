/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 16:39:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT"

int	calc_color(t_scene *scene, t_ray *ray)
{
	
}

void	calc_ray(t_scene *scene, int x, int y, t_ray *ray)
{
	ray->ray_vec = ?;
	ray->intersection ?;
	ray->object = ?;
}

void	calc_corners(t_scene *scene)
{
	scene->camera->corners[0][0] = ?;
	scene->camera->corners[0][1] = ?;
	scene->camera->corners[1][0] = ?;
	scene->camera->corners[1][1] = ?;
}

void	raytracer(mlx_image_t *image, t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	calc_corners(scene);
	i = -1;
	while (++y < image.height)
	{
		j = -1;
		while (++x < image.width)
		{
			calc_ray(scene, x, y, &ray);
			color = calc_color(scene, &ray);
			ft_put_pixel(image, x, y, color);
		}
	}
}
