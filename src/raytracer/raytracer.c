/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/23 15:13:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	compute_viewport(t_minirt *minirt)
{
	t_camera	*camera;
	double		aspect_ratio;

	camera = minirt->scene->camera;
	camera->up.x = 0;
	camera->up.y = 1;
	camera->up.z = 0;
	camera->right = cross(camera->direction, camera->up);
	camera->up = cross(camera->direction, camera->right);
	camera->height = 2 * tan(camera->fov / 2);
	aspect_ratio = minirt->image->width / minirt->image->height;
	camera->width = aspect_ratio * camera->height;
}

void	compute_ray(t_minirt *minirt, int x, int y, t_ray *ray)
{
	t_camera	*camera;
	double		scalex;
	double		scaley;

	camera = minirt->scene->camera;
	scalex = ((double)x / minirt->image->width - 0.5) * camera->width;
	scaley = ((double)y / minirt->image->height - 0.5) * camera->height;
	ray->direction = add(
		multiply(camera->right, scalex),
		multiply(camera->up, scaley));
	ray->direction = normalize(add(ray->direction, camera->direction));
}

void	compute_ray_object_intersection(t_minirt *minirt, t_ray *ray)
{
	t_object	*curr;

	curr = minirt->scene->objects;
	ray->intersection = -1;
	ray->object = NULL;
	while (curr)
	{
		if (curr->type == PLANE)
			calc_plane_intersection(ray, curr, minirt->scene->camera->viewpoint);
		if (curr->type == SPHERE)
			calc_sphere_intersection(ray, curr, minirt->scene->camera->viewpoint);
		if (curr->type == CYLINDER)
			calc_cylinder_intersection(ray, curr, minirt->scene->camera->viewpoint);
		curr = curr->next;
	}
}

void	compute_light_ray(t_minirt *minirt, t_ray *camera_ray, t_spot *spot, t_ray *light_ray)
{
	minirt++;
	light_ray->hitpoint = subtract(multiply(camera_ray->direction,
		camera_ray->intersection), spot->source);
	//	calculate if anything gets in between
	light_ray->object = camera_ray->object;
}

t_vec3	compute_surface(t_vec3 hitpoint, t_object *object)
{
	t_vec3	projected_point;

	if (object->type == SPHERE)
		return (normalize(subtract(hitpoint, object->center)));
	if (object->type == PLANE)
		return (object->direction);
	if (object->type == CYLINDER)
	{
		projected_point = (t_vec3){hitpoint.x, object->center.y, hitpoint.z};
		if (fabs(hitpoint.y - object->center.y) < EPSILON)
			return ((t_vec3){0, -1, 0});
		if (fabs(hitpoint.y - object->center.y) < EPSILON)	// center should be top_cap. Calculate from height
			return ((t_vec3){0, 1, 0});
		return (normalize(subtract(hitpoint, projected_point)));
	}
	return ((t_vec3){0,0,0});
}

int	compute_color(t_minirt *minirt, t_ray *camera_ray)
{
	minirt++;
//	int	color;
/* 	unsigned char	r;
	unsigned char	g;
	unsigned char	b; */

	return (camera_ray->object->color);
/* 	r = (unsigned char)fmin(get_r(camera_ray->object->color) * camera_ray->intersection / 64, 255);
	g = (unsigned char)fmin(get_g(camera_ray->object->color) * camera_ray->intersection / 64, 255);
	b = (unsigned char)fmin(get_b(camera_ray->object->color) * camera_ray->intersection / 64, 255);
	color = get_rgba(r, g, b, 0xff);
	return (color); */

/* 
	t_spot	*spot;
	t_ray	light_ray;
	t_vec3	surface;
	double	diffuse;

	color = camera_ray->object->color;
	spot = minirt->scene->spots;
	while (spot)
	{
		compute_light_ray(minirt, camera_ray, spot, &light_ray);
		surface = compute_surface(light_ray.hitpoint, light_ray.object);
		// compute diffuse lighting
 		diffuse = fmax(dot(surface, light_ray.direction), 0.0);
		r = fmin(get_r(color) * (diffuse * spot->ratio), 255);
		g = fmin(get_g(color) * (diffuse * spot->ratio), 255);
		b = fmin(get_b(color) * (diffuse * spot->ratio), 255);
		color = get_rgba(r, g, b, 0xff * (diffuse * spot->ratio));

		spot = spot->next;
		return (color);
	}
	return (0); */
/* 		for each spot in scene->spots
			trace ray from ray->ray_vec to spot
				if an object is in between:
					return ray->object->color affected by scene->ambient
				if no object is in between
					return ray->object->color affected by scene->ambient 
						and by spot (the more so the closer the spot) */
}

void	raytracer(void *param)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_minirt	*minirt;
	int			color;

	minirt = (t_minirt *)param;
	compute_viewport(minirt);
	y = -1;
	while (++y < minirt->image->height)
	{
		x = -1;
		while (++x < minirt->image->width)
		{
			compute_ray(minirt, x, y, &ray);
			compute_ray_object_intersection(minirt, &ray);
			if (ray.object)
			{
 				color = compute_color(minirt, &ray);
				mlx_put_pixel(minirt->image, x, y, color);
			}
			else
				mlx_put_pixel(minirt->image, x, y, minirt->scene->ambient->color);
		}
	}
}
