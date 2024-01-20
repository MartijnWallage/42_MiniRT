/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/20 14:35:13 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* int	compute_color(t_scene *scene, t_ray *ray)
{
	
		for each spot in scene->spots
			trace ray from ray->ray_vec to spot
				if an object is in between:
					return ray->object->color affected by scene->ambient
				if no object is in between
					return ray->object->color affected by scene->ambient 
						and by spot (the more so the closer the spot)
	
}

void	compute_ray(t_scene *scene, int x, int y, t_ray *ray)
{
	ray->ray_vec = ?;
	ray->intersection ?;
	ray->object = ?;
}

void	compute_corners(t_scene *scene)
{
	scene->camera->corners[0][0] = ?;
	scene->camera->corners[0][1] = ?;
	scene->camera->corners[1][0] = ?;
	scene->camera->corners[1][1] = ?;
}*/

void	compute_image_plane(t_minirt *minirt)
{
	t_camera	*camera;

	camera = minirt->scene->camera;
	camera->up = {0, 1, 0};
	cross(camera->normvect, camera->up, camera->right);
	cross(camera->normvect, camera->right, camera->up);
	camera->width = 2 * tan(camera->fov / 2);
	camera->heigt = camera->width * minirt->image->width / minirt->image->height;
}

void	raytracer(t_minirt *minirt)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	compute_image_plane(minirt);
	i = -1;
	while (++y < image.height)
	{
		j = -1;
		while (++x < image.width)
		{
			compute_ray(scene, x, y, &ray);
			color = compute_color(scene, &ray);
			ft_put_pixel(image, x, y, color);
		}
	}
}
