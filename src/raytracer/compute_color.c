/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/19 12:56:51 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	scale_color(int c, t_real scale)
{
	t_real	rgb[3];

	rgb[0] = fmin((t_real)get_r(c) * scale, 255);
	rgb[1] = fmin((t_real)get_g(c) * scale, 255);
	rgb[2] = fmin((t_real)get_b(c) * scale, 255);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int alpha_shade(int c1, int c2, t_real alpha)
{
	t_real	rgb[3];

 	rgb[0] = (1 - alpha) * (t_real)get_r(c1) + alpha * (t_real)get_r(c2);
	rgb[1] = (1 - alpha) * (t_real)get_g(c1) + alpha * (t_real)get_g(c2);
	rgb[2] = (1 - alpha) * (t_real)get_b(c1) + alpha * (t_real)get_b(c2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	mix_colors(int color1, int color2)
{
	t_real	rgb[3];

	rgb[0] = fmin((t_real)get_r(color1) / 255.0 * (t_real)get_r(color2), 255.0);
	rgb[1] = fmin((t_real)get_g(color1) / 255.0 * (t_real)get_g(color2), 255.0);
	rgb[2] = fmin((t_real)get_b(color1) / 255.0 * (t_real)get_b(color2), 255.0);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int add_colors(int c1, int c2)
{
	t_real	rgb[3];

/* 	rgb[0] = (t_real)(ft_min(get_r(c1) + get_r(c2), 255)) / 2;
	rgb[1] = (t_real)(ft_min(get_g(c1) + get_g(c2), 255)) / 2;
	rgb[2] = (t_real)(ft_min(get_b(c1) + get_b(c2), 255)) / 2; */
	rgb[0] = ft_min(get_r(c1) + get_r(c2), 255);
	rgb[1] = ft_min(get_g(c1) + get_g(c2), 255);
	rgb[2] = ft_min(get_b(c1) + get_b(c2), 255);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	compute_specular(t_spotlight *spotlight, t_ray *camera_ray, t_ray *light_ray)
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

int	compute_diffuse(t_spotlight *spotlight, t_ray *camera_ray, t_ray *light_ray)
{
	t_real	dot_product;

	dot_product = spotlight->diffuse * camera_ray->object->diffuse
		* fmax(dot(camera_ray->normal, multiply(light_ray->direction, -1.0)), 0.0);
	return (scale_color(spotlight->color, dot_product));
}

int	compute_ambient(t_ambient *ambient)
{
	return (scale_color(ambient->color, ambient->ratio));
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	int			obj_color;
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
	obj_color = mix_colors(camera_ray->object->color, add_colors(ambient, diffuse));
	return (add_colors(obj_color, specular));
}

/* int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	float			t;
	t_ray			light_ray;
	t_spotlight		*spotlights;
	int				ambient;
	int				diffuse;
 	t_real			specular_t;
	t_vec3			reflection;


	ret = mix_colors(
			mix_colors(0xff, camera_ray->object->color, camera_ray->object->ambient),
			minirt->scene->ambient.color,
			minirt->scene->ambient.ratio);


	ambient = mix_colors(camera_ray->object->color, minirt->scene->ambient.color);
	ambient = colorScale(ambient, minirt->scene->ambient.color);
//	ambient = shade_colors(0xff, ambient, camera_ray->object->ambient * minirt->scene->ambient.ratio);
	diffuse = 0xff;
	spotlights = minirt->scene->spotlights;
	while (spotlights)
	{
		compute_light_ray(camera_ray, spotlights, &light_ray);
		compute_ray_object_intersection(minirt, &light_ray);
		if (light_ray.object == camera_ray->object)
		{
 			obj_color = mix_colors(camera_ray->object->color, spotlights->color);
			obj_color = shade_colors(0xff, obj_color, spotlights->ratio * camera_ray->object->diffuse);


			t = spotlights->ratio * camera_ray->object->diffuse * fmax(dot(camera_ray->normal,
						multiply(light_ray.direction, -1)), 0.0);
			reflection = get_reflection(light_ray.direction, camera_ray->normal);
  			specular_t = dot(reflection, multiply(camera_ray->direction, -1.0));
			if (specular_t < 0)
				specular_t = 0;
			else
				specular_t = pow(specular_t, 6);
			diffuse = shade_colors(diffuse, spotlights->color, t + specular_t);
		}
		spotlights = spotlights->next;
	}
	return (add_colors(ambient, diffuse));
} */
