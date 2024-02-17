/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/17 17:23:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	mix_colors(int color1, int color2, float ratio)
{
	t_real	rgb[3];

	rgb[0] = (1 - ratio) * (float)get_r(color1) + ratio * (float)get_r(color2);
	rgb[1] = (1 - ratio) * (float)get_g(color1) + ratio * (float)get_g(color2);
	rgb[2] = (1 - ratio) * (float)get_b(color1) + ratio * (float)get_b(color2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

void	compute_light_ray(t_ray *camera_ray, t_spotlights *spotlights, t_ray *light_ray)
{
	t_vec3		hitpoint;

	hitpoint = multiply(camera_ray->direction, camera_ray->intersection);
	hitpoint = add(hitpoint, camera_ray->origin);
	light_ray->origin = spotlights->source;
	light_ray->direction = normalize(subtract(hitpoint, light_ray->origin));
	light_ray->intersection = norm(subtract(hitpoint, light_ray->origin));
	light_ray->object = camera_ray->object;
	light_ray->normal = multiply(camera_ray->normal, 1);
	if (dot(light_ray->normal, light_ray->direction) > 0)
		light_ray->normal = multiply(camera_ray->normal, -1);
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	float			t;
	int				ret;
	t_ray			light_ray;
	t_spotlights	*spotlights;

	ret = mix_colors(camera_ray->object->color,
			minirt->scene->ambient.color,
			minirt->scene->ambient.ratio);
	spotlights = minirt->scene->spotlights;
	while (spotlights)
	{
		compute_light_ray(camera_ray, spotlights, &light_ray);
		compute_ray_object_intersection(minirt, &light_ray);
		if (light_ray.object == camera_ray->object)
		{
			t = spotlights->ratio * fmax(dot(camera_ray->normal,
						multiply(light_ray.direction, -1)), 0.0);
			ret = mix_colors(ret, spotlights->color, t);
		}
		spotlights = spotlights->next;
	}
	return (ret);
}
