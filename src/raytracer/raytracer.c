/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/20 17:30:00 by mwallage         ###   ########.fr       */
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
	camera->up[0] = 0;
	camera->up[1] = 1;
	camera->up[2] = 0;
	cross(camera->normvect, camera->up, camera->right);
	cross(camera->normvect, camera->right, camera->up);
	camera->height = 2 * tan(camera->fov / 2);
	aspect_ratio = minirt->image->width / minirt->image->height;
	camera->width = aspect_ratio * camera->height;
}

void	calc_plane_intersection(t_ray *ray, t_object *iter, t_scene *scene)
{
	double		temp;
	double		factor;
	t_vector	temp_vec;

	temp = dot(ray->normvect, iter->normvect);
	if (temp > -EPSILON && temp < EPSILON)
		return ;
	subtract(iter->center, scene->camera->viewpoint, temp_vec);
	factor = dot(temp_vec, iter->normvect) / dot(ray->normvect, iter->normvect);
	if (factor >= ray->intersection)
	{
		ray->object = iter;
		ray->intersection = factor;
	}
}

void	compute_ray(t_minirt *minirt, int x, int y, t_ray *ray)
{
/* 	double		ndc[2], vpc[2];
	double		scalex, scaley; */
	t_camera	*camera;
	t_vector	product_right_x;
	t_vector	product_up_y;
	t_vector	sum;
	t_object	*iter;

	camera = minirt->scene->camera;
/* 	ndc[0] = x / minirt->image->width;			// convert to normal device coordinates
	ndc[1] = y / minirt->image->height;
	scalex = tan(camera->fov / 2) * (minirt->image->width / minirt->image->height);
	scaley = tan(camera->fov / 2);
	vpc[0] = (2 * ndc[0] - 1) * scalex;			// convert to view plane coordinates
	vpc[1] = (1 - 2 * ndc[1]) * scaley; */
	x = (double)x / minirt->image->width;
	y = (double)y / minirt->image->height;
	x = 2.0 * x - 1.0;
	y = 2.0 * y - 1.0;
	x *= camera->width;
	y *= camera->height;
	multiply(camera->right, x, product_right_x);
	multiply(camera->up, y, product_up_y);
	add(product_right_x, product_up_y, sum);
	add(sum, camera->normvect, ray->normvect);
	normalize(ray->normvect, ray->normvect);
//	printf("Ray %d, %d: %f, %f, %f\n", x, y, ray->normvect[0], ray->normvect[1], ray->normvect[2]);
	iter = minirt->scene->objects;
	ray->intersection = 0;
	ray->object = NULL;
	while (iter)
	{
		if (iter->type == PLANE)
			calc_plane_intersection(ray, iter, minirt->scene);
		iter = iter->next;
	}
	/* ray->intersection ?;
	ray->object = ?; */
}

void	raytracer(t_minirt *minirt)
{
	__uint32_t	x;
	__uint32_t	y;
	t_ray	ray;

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
		}
	}
}
