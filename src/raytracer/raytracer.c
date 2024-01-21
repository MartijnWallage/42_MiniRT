/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 13:23:06 by mwallage         ###   ########.fr       */
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
	t_vec3	product_right_x;
	t_vec3	product_up_y;
	t_object	*iter;
	double		dx, dy;

	camera = minirt->scene->camera;
	dx = (double)x / minirt->image->width;
	dy = (double)y / minirt->image->height;
	dx = (2.0 * dx - 1.0) * camera->width / 2;
	dy = (2.0 * dy - 1.0) * camera->height / 2;
	product_right_x = multiply(camera->right, dx);
	product_up_y = multiply(camera->up, dy);
	ray->normvect = add(product_right_x, product_up_y);
	ray->normvect = add(ray->normvect, camera->normvect);
	ray->normvect = normalize(ray->normvect);
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
	__uint32_t	x;
	__uint32_t	y;
	t_ray	ray;
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
