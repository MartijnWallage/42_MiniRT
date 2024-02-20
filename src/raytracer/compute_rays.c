/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:38:19 by thofting          #+#    #+#             */
/*   Updated: 2024/02/20 11:00:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3	get_hitpoint(t_ray *ray)
{
	return (multiply(ray->direction, ray->intersection));
}

void	compute_light_ray(t_ray *camera_ray, t_spotlight *spot, t_ray *light_ray)
{
	t_vec3		hitpoint;

	hitpoint = add(get_hitpoint(camera_ray), camera_ray->origin);
	light_ray->origin = spot->source;
	light_ray->direction = normalize(subtract(hitpoint, light_ray->origin));
	light_ray->intersection = norm(subtract(hitpoint, light_ray->origin));
	light_ray->object = camera_ray->object;
	light_ray->normal = multiply(camera_ray->normal, 1);
	if (dot(light_ray->normal, light_ray->direction) > 0)
		light_ray->normal = multiply(camera_ray->normal, -1);
}

void	compute_camera_ray(t_minirt *minirt, t_real x, t_real y, t_ray *ray)
{
	t_camera	*camera;
	t_real		scalex;
	t_real		scaley;

	camera = &minirt->scene->camera;
	ray->origin = camera->viewpoint;
	scalex = (x / minirt->image->width - 0.5) * camera->width;
	scaley = (y / minirt->image->height - 0.5) * camera->height;
	ray->direction = add(
			multiply(camera->right, scalex),
			multiply(camera->up, -scaley));
	ray->direction = normalize(add(ray->direction, camera->direction));
	ray->intersection = -1;
	ray->object = NULL;
}
