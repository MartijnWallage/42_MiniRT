/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 11:35:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	mix_colors(int color1, int color2, float ratio)
{
	double	rgb[3];

	rgb[0] = (1 - ratio) * (float)get_r(color1) + ratio * (float)get_r(color2);
	rgb[1] = (1 - ratio) * (float)get_g(color1) + ratio * (float)get_g(color2);
	rgb[2] = (1 - ratio) * (float)get_b(color1) + ratio * (float)get_b(color2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	float	t;
	int		ret;
	t_ray	light_ray;

	ret = mix_colors(camera_ray->object->color,
			minirt->scene->ambient.color,
			minirt->scene->ambient.ratio);
	if (minirt->scene->spot)
	{
		compute_light_ray(camera_ray, minirt->scene->spot, &light_ray);
		compute_ray_object_intersection(minirt, &light_ray);
		if (light_ray.object == camera_ray->object)
		{
			t = minirt->scene->spot->ratio
				* fmax(dot(camera_ray->normal,
						multiply(light_ray.direction, -1)), 0.0);
			ret = mix_colors(ret, 0xffffffff, t);
		}
	}
	return (ret);
}
