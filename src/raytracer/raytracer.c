/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 17:24:52 by mwallage         ###   ########.fr       */
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
		if (curr->type == DISK)
			compute_disk_intersection(ray, curr);
		curr = curr->next;
	}
}

void	raytracer(void *param)
{
	uint32_t	y;
	uint32_t	x;
	t_minirt	*minirt;
	int			color;
	t_ray		camera;

	if (BONUS)
	{
		multi_thread(param);
		return ;
	}
	minirt = (t_minirt *)param;
	compute_viewport(minirt);
	y = -1;
	while (++y < minirt->image->height)
	{
		x = -1;
		while (++x < minirt->image->width)
		{
			compute_camera_ray(minirt, x, y, &camera);
			compute_ray_object_intersection(minirt, &camera);
			color = compute_color(minirt, &camera);
			ft_put_pixel(minirt->image, x, y, color);
		}
	}
}
