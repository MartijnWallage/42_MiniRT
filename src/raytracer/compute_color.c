/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/26 18:56:28 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	compute_specular(int *specular, t_spotlight *spotlight,
	t_ray *camera, t_ray *light)
{
	t_real		dot_ray_normal;
	t_vec3		reflection;
	t_real		scalar;
	t_object	*obj;
	int			new_specular;

	obj = camera->object;
	dot_ray_normal = dot(light->direction, camera->normal);
	reflection = multiply(camera->normal, 2.0 * dot_ray_normal);
	reflection = subtract(light->direction, reflection);
	scalar = dot(reflection, camera->direction);
	scalar = ft_abs(fmin(scalar, 0.0));
	scalar = pow(scalar, obj->shininess);
	scalar = (1 - obj->diffuse) * (spotlight->specular) * scalar;
	new_specular = scale_color(spotlight->color, scalar);
	*specular = add_colors(*specular, new_specular);
}

void	compute_diffuse(int *diffuse, t_spotlight *spotlight,
	t_ray *camera, t_ray *light)
{
	t_real	dot_product;
	int		new_diffuse;

	dot_product = spotlight->diffuse * camera->object->diffuse
		* fmax(dot(camera->normal, multiply(light->direction, -1.0)),
			0.0);
	new_diffuse = scale_color(spotlight->color, dot_product);
	*diffuse = add_colors(*diffuse, new_diffuse);
}

static int	compute_ambient(t_ambient *ambient)
{
	return (scale_color(ambient->color, ambient->ratio));
}

int	compute_color(t_minirt *minirt, t_ray *camera)
{
	int			color;
	int			specular;
	t_ray		light;
	t_spotlight	*spotlights;

	if (camera->object == NULL)
		return (0xff);
	color = compute_ambient(&(minirt->scene->ambient));
	spotlights = minirt->scene->spotlights;
	if (spotlights == NULL)
		return (mix_colors(camera->object->color, color));
	specular = 0xff;
	while (spotlights)
	{
		compute_light_ray(camera, spotlights, &light);
		compute_ray_object_intersection(minirt, &light);
		if (light.object == camera->object)
		{
			compute_diffuse(&color, spotlights, camera, &light);
			compute_specular(&specular, spotlights, camera, &light);
		}
		spotlights = spotlights->next;
	}
	return (add_colors(mix_colors(camera->object->color, color), specular));
}
