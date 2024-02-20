/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:38:19 by thofting          #+#    #+#             */
/*   Updated: 2024/02/20 14:04:28 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_hitpoint(t_ray *ray)
{
	return (multiply(ray->direction, ray->intersection));
}

void	compute_light_ray(t_ray *camera, t_spotlight *spot, t_ray *light)
{
	t_vec3		hitpoint;

	hitpoint = add(get_hitpoint(camera), camera->origin);
	light->origin = spot->source;
	light->direction = normalize(subtract(hitpoint, light->origin));
	light->intersection = norm(subtract(hitpoint, light->origin));
	light->object = camera->object;
	light->normal = multiply(camera->normal, 1);
	if (dot(light->normal, light->direction) > 0)
		light->normal = multiply(camera->normal, -1);
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
