/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 14:11:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	compute_specular(t_spotlight *spotlight, t_ray *camera, t_ray *light)
{
	t_real		dot_ray_normal;
	t_vec3		scaled_normal;
	t_vec3		reflection;
	t_real		scalar;
	t_object	*obj;

	obj = camera->object;
	dot_ray_normal = dot(light->direction, camera->normal);
	scaled_normal = multiply(camera->normal, 2.0 * dot_ray_normal);
	reflection = subtract(light->direction, scaled_normal);
	scalar = (1 - obj->diffuse) * (spotlight->specular)
		* pow(fmin(dot(reflection, camera->direction), 0.0), obj->shininess);
	return (scale_color(spotlight->color, scalar));
}

int	compute_diffuse(t_spotlight *spotlight, t_ray *camera, t_ray *light)
{
	t_real	dot_product;

	dot_product = spotlight->diffuse * camera->object->diffuse
		* fmax(dot(camera->normal, multiply(light->direction, -1.0)),
			0.0);
	return (scale_color(spotlight->color, dot_product));
}

static int	compute_ambient(t_ambient *ambient)
{
	return (scale_color(ambient->color, ambient->ratio));
}

int	compute_color(t_minirt *minirt, t_ray *camera)
{
	int			ambient;
	int			diffuse;
	int			specular;
	t_ray		light;
	t_spotlight	*spotlights;

	if (camera->object == NULL)
		return (0xff);
	ambient = compute_ambient(&(minirt->scene->ambient));
	spotlights = minirt->scene->spotlights;
	if (spotlights == NULL)
		return (ambient);
	diffuse = 0xff;
	specular = 0xff;
	while (spotlights)
	{
		compute_light_ray(camera, spotlights, &light);
		compute_ray_object_intersection(minirt, &light);
		if (light.object == camera->object)
		{
			diffuse = add_colors(diffuse,
					compute_diffuse(spotlights, camera, &light));
			specular = add_colors(specular,
					compute_specular(spotlights, camera, &light));
		}
		spotlights = spotlights->next;
	}
	return (add_colors(mix_colors(camera->object->color,
				add_colors(ambient, diffuse)), specular));
}
