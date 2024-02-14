/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 14:10:44 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	compute_viewport(t_minirt *minirt)
{
	t_camera	*camera;
	double		aspect_ratio;

	camera = minirt->scene->camera;
	camera->right = normalize(cross(camera->direction, camera->up));
	camera->up = normalize(cross(camera->right, camera->direction));
	camera->height = 2.0 * tan(camera->fov / 2);
	aspect_ratio = minirt->image->width / minirt->image->height;
	camera->width = aspect_ratio * camera->height;
}

void	compute_camera_ray(t_minirt *minirt, int x, int y, t_ray *ray)
{
	t_camera	*camera;
	double		scalex;
	double		scaley;

	camera = minirt->scene->camera;
	ray->origin = camera->viewpoint;
	scalex = ((double)x / minirt->image->width - 0.5) * camera->width;
	scaley = ((double)y / minirt->image->height - 0.5) * camera->height;
	ray->direction = add(
		multiply(camera->right, scalex),
		multiply(camera->up, -scaley));
	ray->direction = normalize(add(ray->direction, camera->direction));
	ray->intersection = -1;
	ray->object = NULL;
}

void	compute_ray_object_intersection(t_minirt *minirt, t_ray *ray)
{
	t_object	*curr;

	curr = minirt->scene->objects;
	while (curr)
	{
		if (curr->type == PLANE)
			calc_plane_intersection(ray, curr);
		if (curr->type == SPHERE)
			calc_sphere_intersection(ray, curr);
		if (curr->type == CYLINDER)
			calc_cylinder_intersection(ray, curr);
		curr = curr->next;
	}
}

void	compute_light_ray(t_ray *camera_ray, t_spot *spot, t_ray *light_ray)
{
	t_vec3		hitpoint;

	hitpoint = add(multiply(camera_ray->direction, camera_ray->intersection), camera_ray->origin);
	light_ray->origin = spot->source;
	light_ray->direction = normalize(subtract(hitpoint, light_ray->origin));
	light_ray->intersection = norm(subtract(hitpoint, light_ray->origin));
	light_ray->object = camera_ray->object;
	light_ray->normal = multiply(camera_ray->normal, 1);
	if (dot(light_ray->normal, light_ray->direction) > 0)
		light_ray->normal = multiply(camera_ray->normal, -1);
}

t_vec3 reflect(t_vec3 v, t_vec3 n) 
{
    float n_dot_v = dot(n, v);
    t_vec3 result = { v.x - 2 * n_dot_v * n.x, v.y - 2 * n_dot_v * n.y, v.z - 2 * n_dot_v * n.z };
    return (result);
}


double	mix_colors(double color1, double color2, double ratio)
{
	return ((1 - ratio) * color1 + ratio * color2);
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	double	t = minirt->scene->ambient->ratio;
	double	rgb[3];
	t_ray	light_ray;

	rgb[0] = mix_colors(get_r(camera_ray->object->color) * minirt->scene->ambient->ratio, get_r(minirt->scene->ambient->color), minirt->scene->ambient->ratio);
	rgb[1] = mix_colors(get_g(camera_ray->object->color) * minirt->scene->ambient->ratio, get_g(minirt->scene->ambient->color), minirt->scene->ambient->ratio);
	rgb[2] = mix_colors(get_b(camera_ray->object->color) * minirt->scene->ambient->ratio, get_b(minirt->scene->ambient->color), minirt->scene->ambient->ratio);
	if (minirt->scene->spot)
	{
		compute_light_ray(camera_ray, minirt->scene->spot, &light_ray);
		compute_ray_object_intersection(minirt, &light_ray);
		if (light_ray.object == camera_ray->object)
		{
			t = minirt->scene->spot->ratio * fmax(dot(camera_ray->normal, multiply(light_ray.direction, -1)), 0.0);
			rgb[0] = mix_colors(rgb[0], 0.5 * (0xff + get_r(camera_ray->object->color)), t);
			rgb[1] = mix_colors(rgb[1], 0.5 * (0xff + get_g(camera_ray->object->color)), t);
			rgb[2] = mix_colors(rgb[2], 0.5 * (0xff + get_b(camera_ray->object->color)), t);
		}
	}
	return (get_rgba(rgb[0], rgb[1], rgb[2], 0xff));
}

void	raytracer(void *param)
{
	uint32_t	y;
	uint32_t	x;
	t_ray		camera_ray;
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	compute_viewport(minirt);
	y = -1;
	while (++y < minirt->image->height)
	{
		x = -1;
		while (++x < minirt->image->width)
		{
			compute_camera_ray(minirt, x, y, &camera_ray);
			compute_ray_object_intersection(minirt, &camera_ray);
			if (camera_ray.object)
				ft_put_pixel(minirt->image, x, y, compute_color(minirt, &camera_ray));
			else
				ft_put_pixel(minirt->image, x, y, 0xFF);
		}
	}
}