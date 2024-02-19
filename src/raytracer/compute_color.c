/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:46 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/19 08:35:01 by mwallage         ###   ########.fr       */
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

	rgb[0] = (t_real)get_r(color1) / 255.0 * (t_real)get_r(color2);
	rgb[1] = (t_real)get_g(color1) / 255.0 * (t_real)get_g(color2);
	rgb[2] = (t_real)get_b(color1) / 255.0 * (t_real)get_b(color2);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

int add_colors(int c1, int c2)
{
	t_real	rgb[3];

/* 	rgb[0] = (t_real)(ft_min(get_r(color1) + get_r(color2), 255)) / 2;
	rgb[1] = (t_real)(ft_min(get_g(color1) + get_g(color2), 255)) / 2;
	rgb[2] = (t_real)(ft_min(get_b(color1) + get_b(color2), 255)) / 2; */
	rgb[0] = ft_min(get_r(c1) + get_r(c2), 255);
	rgb[1] = ft_min(get_g(c1) + get_g(c2), 255);
	rgb[2] = ft_min(get_b(c1) + get_b(c2), 255);
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

int	colorScale(int c, t_real scale)
{
	t_real	rgb[3];

	if (scale < 0)
		return (c);
	rgb[0] = fmin((t_real)get_r(c) * scale, 255);
	rgb[1] = fmin((t_real)get_g(c) * scale, 255);
	rgb[2] = fmin((t_real)get_b(c) * scale, 255);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

t_vec3	get_reflection(t_ray *ray, t_vec3 normal)
{
	t_real	dot_ray_normal;
	t_vec3	scaled_normal;
	t_vec3	ray_inverted;

	ray_inverted = multiply(ray->direction, -1.0);
	dot_ray_normal = dot(ray_inverted, normal);
	if (dot_ray_normal <= 0)
		return ((t_vec3){0,0,0});
	scaled_normal = multiply(normal, 2.0 * dot_ray_normal);
	return (subtract(ray_inverted, scaled_normal));
}

int	compute_specular(t_spotlight *spotlights, t_ray *camera_ray, t_ray *light_ray)
{
	t_vec3	reflection;
	t_real	scalar;

	reflection = get_reflection(light_ray, camera_ray->normal);
	if (reflection.x == 0 && reflection.y == 0 && reflection.z == 0)
		return (0xff);
  	scalar = 0.5 * pow(dot(reflection, multiply(camera_ray->direction, -1.0)), 12);
	return (colorScale(spotlights->color, scalar));
}

int	compute_diffuse(t_spotlight *spotlight, t_ray *camera_ray, t_ray *light_ray)
{
	t_real	dot_product;

	dot_product = spotlight->ratio * camera_ray->object->diffuse
		* fmax(dot(camera_ray->normal, multiply(light_ray->direction, -1.0)), 0.0);
	return (colorScale(spotlight->color, dot_product));
}

int	compute_ambient(t_ambient *ambient)
{
	return (colorScale(ambient->color, ambient->ratio));
}

int	compute_phong(t_minirt *minirt, t_ray *camera_ray)
{
	int			ambient;
	int			diffuse;
	int			specular;
	t_ray		light_ray;
	t_spotlight	*spotlights;

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
	return (add_colors(add_colors(diffuse, specular), ambient));
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	int	total_light;
	int	obj_color;
	int	final_color;

	if (camera_ray->object == NULL)
		return (0xff);
	total_light = compute_phong(minirt, camera_ray);
	obj_color = camera_ray->object->color;
	final_color = mix_colors(obj_color, total_light);
	return (final_color);
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
