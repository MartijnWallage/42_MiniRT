/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:38:51 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/17 11:41:47 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_dt(t_real dt[2][2], t_ray *ray, t_object *cyl,
	t_cyl *ints)
{
	t_vec3		temp;

	if (dt[0][0] > 0)
	{
		temp = subtract(multiply(ray->direction, dt[0][0]), ints->b);
		dt[1][0] = dot(cyl->direction, temp);
		if (dt[1][0] < -cyl->height / 2 || dt[1][0] > cyl->height / 2)
			dt[0][0] = -1;
	}
	if (dt[0][1] > 0)
	{
		temp = subtract(multiply(ray->direction, dt[0][1]), ints->b);
		dt[1][1] = dot(cyl->direction, temp);
		if (dt[1][1] < -cyl->height / 2 || dt[1][1] > cyl->height / 2)
			dt[0][1] = -1;
	}
}

static void	compute_cyl_hull(t_cyl *ints, t_ray *ray, t_object *cyl)
{
	t_real		norm_nxa2;
	t_real		delta;
	t_real		dt[2][2];
	int			type;

	norm_nxa2 = norm2(ints->nxa);
	if (norm_nxa2 < EPSILON)
		return ;
	delta = norm_nxa2 * pow2(cyl->radius) - pow2(dot(ints->b, ints->nxa));
	if (delta < 0)
		return ;
	dt[1][1] = dot(ints->nxa, ints->b_x_a);
	dt[0][0] = (dt[1][1] + sqrt(delta)) / norm_nxa2;
	dt[0][1] = (dt[1][1] - sqrt(delta)) / norm_nxa2;
	dt[1][0] = 0;
	dt[1][1] = 0;
	check_dt(dt, ray, cyl, ints);
	type = get_min_positive(dt[0][0], dt[0][1]);
	if (type == -1)
		return ;
	ints->t_hull = dt[1][type];
	ints->d_hull = dt[0][type];
}


static t_real	compute_d(t_ray *ray, t_object *cyl, t_vec3 cap_center, t_real dot_ray_cyl)
{
	t_real	d;

	d = dot(cyl->direction, cap_center) / dot_ray_cyl;
	if (norm2(subtract(multiply(ray->direction, d), cap_center)) >= pow2(cyl->radius))
		return (-1);
	return (d);
}

static t_real	compute_cyl_cap(t_ray *ray, t_object *cyl)
{
	t_real		dot_ray_cyl;
	t_vec3		cap_center;
	t_real		d[2];
	t_vec3		half_axis;

	dot_ray_cyl = dot(ray->direction, cyl->direction);
	if (ft_abs(dot_ray_cyl) < EPSILON)
		return (-1);
	half_axis = multiply(cyl->direction, cyl->height / 2);
	cap_center = subtract(add(cyl->center, half_axis), ray->origin);
	d[0] = compute_d(ray, cyl, cap_center, dot_ray_cyl);
	cap_center = subtract(subtract(cyl->center, half_axis), ray->origin);
	d[1] = compute_d(ray, cyl, cap_center, dot_ray_cyl);
	if (d[0] < 0 && d[1] < 0)
		return (-1);
	return (d[get_min_positive(d[0], d[1])]);
}

void	compute_cyl_intersection(t_ray *ray, t_object *cyl)
{
	t_cyl	ints;
	t_real	d_cap;

	ints = init_ints_struct(ray, cyl);
	compute_cyl_hull(&ints, ray, cyl);
	d_cap = compute_cyl_cap(ray, cyl);
	if (is_first_visible(ints.d_hull, d_cap, ray->intersection))
	{
		ray->object = cyl;
		ray->intersection = ints.d_hull;
		ray->normal = subtract(get_hitpoint(ray), ints.b);
 		ray->normal = normalize(subtract(ray->normal,
			multiply(cyl->direction, ints.t_hull)));
	}
	else if (is_first_visible(d_cap, ints.d_hull, ray->intersection))
	{
		ray->object = cyl;
		ray->intersection = d_cap;
		ray->normal = cyl->direction;
	}
	if (ray->object && dot(ray->normal, ray->direction) > 0)
		ray->normal = multiply(ray->normal, -1);
}
