/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 13:43:21 by mwallage         ###   ########.fr       */
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
*/

void	compute_image_plane(t_minirt *minirt)
{
	t_camera	*camera;
	double		aspect_ratio;

	camera = minirt->scene->camera;
	camera->up.x = 0;
	camera->up.y = 1;
	camera->up.z = 0;
	camera->right = cross(camera->normvect, camera->up);
	camera->up = cross(camera->normvect, camera->right);
	camera->height = 2 * tan(camera->fov / 2);
	aspect_ratio = minirt->image->width / minirt->image->height;
	camera->width = aspect_ratio * camera->height;
}

void	compute_ray(t_minirt *minirt, int x, int y, t_ray *ray)
{
	t_camera	*camera;
	t_object	*iter;
	double		scalex;
	double		scaley;

	camera = minirt->scene->camera;
	scalex = ((double)x / minirt->image->width - 0.5) * camera->width;
	scaley = ((double)y / minirt->image->height - 0.5) * camera->height;
	ray->normvect = add(
		multiply(camera->right, scalex),
		multiply(camera->up, scaley));
	ray->normvect = normalize(add(ray->normvect, camera->normvect));
	iter = minirt->scene->objects;
	ray->intersection = -1;
	ray->object = NULL;
	while (iter)
	{
		if (iter->type == PLANE)
			calc_plane_intersection(ray, iter, minirt->scene);
		if (iter->type == SPHERE)
			calc_sphere_intersection(ray, iter, minirt->scene);
		if (iter->type == CYLINDER)
			calc_cylinder_intersection(ray, iter, minirt->scene);
		iter = iter->next;
	}
}

void	raytracer(void *params)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_minirt	*minirt;

	minirt = (t_minirt *)params;
	compute_image_plane(minirt);
	y = -1;
	while (++y < minirt->image->height)
	{
		x = -1;
		while (++x < minirt->image->width)
		{
			compute_ray(minirt, x, y, &ray);
// 			color = compute_color(scene, &ray);
			if (ray.object)
				mlx_put_pixel(minirt->image, x, y, ray.object->color);
			else
				mlx_put_pixel(minirt->image, x, y, minirt->scene->ambient->color);
		}
	}
}
