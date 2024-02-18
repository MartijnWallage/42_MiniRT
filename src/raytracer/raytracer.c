/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/18 11:52:37 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	compute_viewport(t_minirt *minirt)
{
	t_camera	*camera;
	t_real		aspect_ratio;

	camera = &minirt->scene->camera;
	camera->right = normalize(cross(camera->direction, camera->up));
	camera->up = normalize(cross(camera->right, camera->direction));
	camera->height = 2.0 * tan(camera->fov / 2);
	aspect_ratio = minirt->image->width / minirt->image->height;
	camera->width = aspect_ratio * camera->height;
}

void	compute_ray_object_intersection(t_minirt *minirt, t_ray *ray)
{
	t_object	*curr;

	curr = minirt->scene->objects;
	while (curr)
	{
		if (curr->type == PLANE)
			compute_plane_intersection(ray, curr);
		if (curr->type == SPHERE)
			compute_sphere_intersection(ray, curr);
		if (curr->type == CYLINDER)
			compute_cyl_intersection(ray, curr);
		curr = curr->next;
	}
}

static void	set_rgb_array(int rgb[3], int r, int g, int b)
{
	if (r == -1)
	{
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	else
	{
		rgb[0] += r;
		rgb[1] += g;
		rgb[2] += b;
	}
}

static int	get_smooth_color(t_minirt *rt, uint32_t x, uint32_t y)
{
	int		color;
	int		a[3];
	t_ray	camera_ray;
	int		i;
	int		j;

	i = -SIZE_ANTIALISING - 1;
	set_rgb_array(a, -1, -1, -1);
	while (++i < SIZE_ANTIALISING + 1)
	{
		j = -SIZE_ANTIALISING - 1;
		while (++j < SIZE_ANTIALISING + 1)
		{
			compute_camera_ray(rt, (t_real)x + (t_real)j / \
				(2 * (SIZE_ANTIALISING + 1)), (t_real)y + \
				(t_real)i / (2 * (SIZE_ANTIALISING + 1)), &camera_ray);
			compute_ray_object_intersection(rt, &camera_ray);
			if (camera_ray.object)
				color = compute_color(rt, &camera_ray);
			else
				color = 0xff;
			set_rgb_array(a, get_r(color), get_g(color), get_b(color));
		}
	}
	return (get_rgba(a[0] / rt->num, a[1] / rt->num, a[2] / rt->num, 255));
}

void	raytracer(void *param)
{
	uint32_t	y;
	uint32_t	x;
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
			color = get_smooth_color(minirt, x, y);
			ft_put_pixel(minirt->image, x, y, color);
		}
	}
}
