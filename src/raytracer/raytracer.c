/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:02:05 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/20 15:27:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* int	compute_color(t_scene *scene, t_ray *ray)
{
	
		for each spot in scene->spots
			trace ray from ray->ray_vec to spot
				if an object is in between:
					return ray->object->color affected by scene->ambient
				if no object is in between
					return ray->object->color affected by scene->ambient 
						and by spot (the more so the closer the spot)
	
}
*/

void	compute_image_plane(t_minirt *minirt)
{
	t_camera	*camera;


	camera = minirt->scene->camera;
	camera->up[0] = 0;
	camera->up[1] = 1;
	camera->up[2] = 0;
	cross(camera->normvect, camera->up, camera->right);
	cross(camera->normvect, camera->right, camera->up);
	camera->width = 2 * tan(camera->fov / 2);
	camera->height = camera->width * minirt->image->width / minirt->image->height;
}

void	compute_ray(t_minirt *minirt, int x, int y, t_ray *ray)
{
	double		imageplane_x;
	double		imageplane_y;
	t_camera	*camera;
	t_vector	product_right_x;
	t_vector	product_up_y;
	t_vector	sum;

	camera = minirt->scene->camera;
	imageplane_x = (x + 0.5) / minirt->image->width - 0.5;
	imageplane_y = (y + 0.5) / minirt->image->height - 0.5;
//	printf("x: %f\ny: %f\n", imageplane_x, imageplane_y);
	multiply(camera->right, imageplane_x, product_right_x);
	multiply(camera->up, imageplane_y, product_up_y);
//	printf("camera->right: %f, %f, %f\n", camera->right[0], camera->right[1], camera->right[2]);
	add(product_right_x, product_up_y, sum);
	normalize(sum, ray->normvect);
	printf("Ray %d, %d: %f, %f, %f\n", x, y, ray->normvect[0], ray->normvect[1], ray->normvect[2]);
	/* ray->intersection ?;
	ray->object = ?; */
}

void	raytracer(t_minirt *minirt)
{
	__uint32_t	x;
	__uint32_t	y;
	t_ray	ray;

	compute_image_plane(minirt);
	y = -1;
	while (++y < minirt->image->height)
	{
		x = -1;
		while (++x < minirt->image->width)
		{
			compute_ray(minirt, x, y, &ray);
/* 			color = compute_color(scene, &ray);
			ft_put_pixel(image, x, y, color); */
		}
	}
}
