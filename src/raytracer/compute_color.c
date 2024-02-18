/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/18 17:14:08 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	shade_colors(int color1, int color2, float ratio)
{
	t_real	rgb[3];

	rgb[0] = (1 - ratio) * (float)get_r(color1) + ratio * (float)get_r(color2);
	rgb[1] = (1 - ratio) * (float)get_g(color1) + ratio * (float)get_g(color2);
	rgb[2] = (1 - ratio) * (float)get_b(color1) + ratio * (float)get_b(color2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	mix_colors(int color1, int color2)
{
	t_real	rgb[3];

	rgb[0] = (t_real)get_r(color1) / 255 * (t_real)get_r(color2);
	rgb[1] = (t_real)get_g(color1) / 255 * (t_real)get_g(color2);
	rgb[2] = (t_real)get_b(color1) / 255 * (t_real)get_b(color2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int add_colors(int color1, int color2)
{
	t_real	rgb[3];

	rgb[0] = (t_real)(get_r(color1) + get_r(color2)) / 2;
	rgb[1] = (t_real)(get_g(color1) + get_g(color2)) / 2;
	rgb[2] = (t_real)(get_b(color1) + get_b(color2)) / 2;
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	add_three_colors(int color1, int color2, int color3)
{
	t_real	rgb[3];

	rgb[0] = (t_real)(get_r(color1) + get_r(color2) + get_r(color3)) / 3;
	rgb[1] = (t_real)(get_g(color1) + get_g(color2) + get_g(color3)) / 3;
	rgb[2] = (t_real)(get_b(color1) + get_b(color2) + get_b(color3)) / 3;
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	colorAdd(int c1, int c2)
{
	int	rgb[3];

	rgb[0] = get_r(c1) + get_r(c2);
	rgb[1] = get_g(c1) + get_g(c2);
	rgb[2] = get_b(c1) + get_b(c2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int	colorScale(int c, t_real scale)
{
	t_real	rgb[3];

	rgb[0] = (t_real)get_r(c) * scale;
	rgb[1] = (t_real)get_g(c) * scale;
	rgb[2] = (t_real)get_b(c) * scale;
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

t_vec3	get_reflection(t_vec3 ray, t_vec3 normal)
{
	t_real	dot_ray_normal;
	t_vec3	scaled_normal;

	dot_ray_normal = dot(ray, normal);
	scaled_normal = multiply(normal, 2.0 * dot_ray_normal);
	return (subtract(scaled_normal, ray));
}

int	compute_ambient(t_ambient *ambient)
{
	return (colorScale(ambient->color, ambient->ratio));
}

int	compute_diffuse(t_spotlight *spotlights, t_vec3 normal, t_vec3 light_direction)
{
	t_real	dot_product;

	if (spotlights == NULL)
		return (0xff);
	dot_product = dot(normal, multiply(light_direction, -1.0));
	if (dot <= 0)
		dot_product = 0;
	return (shade_colors(0xff, spotlights->color, dot_product));
}

int	compute_phong(t_minirt *minirt, t_ray *camera_ray)
{
	int		ambient;
 	int		diffuse;
//	int		specular;
	t_ray	light_ray;

	ambient = compute_ambient(&(minirt->scene->ambient));
 	compute_light_ray(camera_ray, minirt->scene->spotlights, &light_ray);
	compute_ray_object_intersection(minirt, &light_ray);
	diffuse = 0xff;
	if (light_ray.object == camera_ray->object)
		diffuse = compute_diffuse(minirt->scene->spotlights, camera_ray->normal, light_ray.direction);
//	specular = compute_specular();
	return (diffuse);
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	int	total_light;
	int	obj_color;
	int	color;

	total_light = compute_phong(minirt, camera_ray);
	obj_color = camera_ray->object->color;
	color = mix_colors(total_light, obj_color);
	return (color);
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
