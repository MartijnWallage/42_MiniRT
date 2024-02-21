/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:21:52 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/21 17:32:15 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static int	anti_alias(t_minirt *minirt, uint32_t x, uint32_t y)
{
	int		color;
	int		a[3];
	t_ray	camera_ray;
	int		i;
	int		j;

	i = -minirt->antialias - 1;
	set_rgb_array(a, -1, -1, -1);
	while (++i < minirt->antialias + 1)
	{
		j = -minirt->antialias - 1;
		while (++j < minirt->antialias + 1)
		{
			compute_camera_ray(minirt, (t_real)x + (t_real)j
				/ (2 * (minirt->antialias + 1)), (t_real)y
				+ (t_real)i / (2 * (minirt->antialias + 1)), &camera_ray);
			compute_ray_object_intersection(minirt, &camera_ray);
			color = compute_color(minirt, &camera_ray);
			set_rgb_array(a, get_r(color), get_g(color), get_b(color));
		}
	}
	return (get_rgba(a[0] / minirt->num, a[1] / minirt->num, a[2]
			/ minirt->num, 255));
}

void	*init_thread(void *param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	max_y;
	t_minirt	*minirt;
	t_row		*group;

	group = (t_row *)param;
	minirt = group->minirt;
	y = group->index * *group->rows_per_group - 1;
	if (group->index == CORES - 1)
		max_y = minirt->image->height;
	else
		max_y = y + 1 + *group->rows_per_group;
	while (++y < max_y)
	{
		x = -1;
		while (++x < minirt->image->width)
			ft_put_pixel(minirt->image, x, y, anti_alias(minirt, x, y));
	}
	return (NULL);
}

void	multi_thread(t_minirt *minirt)
{
	uint32_t	i;
	t_row		groups[CORES];
	pthread_t	threads[CORES];
	uint32_t	rows_per_group;	

	rows_per_group = minirt->image->height / CORES;
	i = -1;
	while (++i < CORES)
	{
		groups[i].index = i;
		groups[i].minirt = minirt;
		groups[i].rows_per_group = &rows_per_group;
		pthread_create(&(threads[i]), NULL, &init_thread, &groups[i]);
	}
	i = -1;
	while (++i < CORES)
		pthread_join(threads[i], NULL);
}
