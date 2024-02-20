/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 10:59:28 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static int	compute_specular(t_spotlight *spotlight, t_ray *camera_ray, t_ray *light_ray)
{
	t_real		dot_ray_normal;
	t_vec3		scaled_normal;
	t_vec3		reflection;
	t_real		scalar;
	t_object	*obj;

	obj = camera_ray->object;
	dot_ray_normal = dot(light_ray->direction, camera_ray->normal);
	scaled_normal = multiply(camera_ray->normal, 2.0 * dot_ray_normal);
	reflection = subtract(light_ray->direction, scaled_normal);
	scalar = (1 - obj->diffuse) * (spotlight->specular)
		* pow(fmin(dot(reflection, camera_ray->direction), 0.0), obj->shininess);
	return (scale_color(spotlight->color, scalar));
}

static int	compute_diffuse(t_spotlight *spotlight, t_ray *camera_ray, t_ray *light_ray)
{
	t_real	dot_product;

	dot_product = spotlight->diffuse * camera_ray->object->diffuse
		* fmax(dot(camera_ray->normal, multiply(light_ray->direction, -1.0)), 0.0);
	return (scale_color(spotlight->color, dot_product));
}

static int	compute_ambient(t_ambient *ambient)
{
	return (scale_color(ambient->color, ambient->ratio));
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	int			ambient;
	int			diffuse;
	int			specular;
	t_ray		light_ray;
	t_spotlight	*spotlights;

	if (camera_ray->object == NULL)
		return (0xff);
	ambient = compute_ambient(&(minirt->scene->ambient));
	spotlights = minirt->scene->spotlights;
	if (spotlights == NULL)
		return (ambient);
	diffuse = 0xff;
	specular = 0xff;
	while (spotlights)
	{
	 	compute_light_ray(camera_ray, spotlights, &light_ray);
		compute_ray_object_intersection(minirt, &light_ray);
		if (light_ray.object == camera_ray->object)
		{
			diffuse = add_colors(diffuse, compute_diffuse(spotlights, camera_ray, &light_ray));
			specular = add_colors(specular, compute_specular(spotlights, camera_ray, &light_ray));
		}
		spotlights = spotlights->next;
	}
	return (add_colors(
		mix_colors(camera_ray->object->color, add_colors(ambient, diffuse)), 
		specular));
}
