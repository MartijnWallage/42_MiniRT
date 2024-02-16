/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:38:51 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 16:20:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_dt(t_real dt[2][2], t_ray *ray, t_object *cyl,
	t_cylinder *ints)
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

static void	compute_cyl_hull(t_cylinder *ints, t_ray *ray, t_object *cylinder)
{
	t_real		norm_nxa2;
	t_real		delta;
	t_real		dt[2][2];
	int			type;

	norm_nxa2 = norm2(ints->nxa);
	if (norm_nxa2 < EPSILON)
		return ;
	delta = norm_nxa2 * pow2(cylinder->radius) - pow2(dot(ints->b, ints->nxa));
	if (delta < 0)
		return ;
	dt[1][1] = dot(ints->nxa, ints->b_x_a);
	dt[0][0] = (dt[1][1] + sqrt(delta)) / norm_nxa2;
	dt[0][1] = (dt[1][1] - sqrt(delta)) / norm_nxa2;
	dt[1][0] = 0;
	dt[1][1] = 0;
	check_dt(dt, ray, cylinder, ints);
	type = get_min_positive(dt[0][0], dt[0][1]);
	if (type == -1)
		return ;
	ints->t_hull = dt[1][type];
	ints->d_hull = dt[0][type];
}

static void	compute_cyl_cap(t_cylinder *ints, t_ray *ray, t_object *cylinder)
{
	t_real		dot_ray_cyl;
	t_vec3		cap_center;
	t_real		d[2];
	int			type;
	t_vec3		half_axis;

	dot_ray_cyl = dot(ray->direction, cylinder->direction);
	if (ft_abs(dot_ray_cyl) < EPSILON)
		return ;
	half_axis = multiply(cylinder->direction, cylinder->height / 2);
	cap_center = subtract(add(cylinder->center, half_axis), ray->origin);
	d[0] = dot(cylinder->direction, cap_center) / dot_ray_cyl;
	if (norm2(subtract(multiply(ray->direction, d[0]), cap_center))
		>= pow2(cylinder->radius))
		d[0] = -1;
	cap_center = subtract(subtract(cylinder->center, half_axis), ray->origin);
	d[1] = dot(cylinder->direction, cap_center) / dot_ray_cyl;
	if (norm2(subtract(multiply(ray->direction, d[1]), cap_center))
		>= pow2(cylinder->radius))
		d[1] = -1;
	type = get_min_positive(d[0], d[1]);
	if (type == -1)
		return ;
	ints->orientation_cap = -1;
	ints->d_cap = d[type];
}

void	compute_cylinder_intersection(t_ray *ray, t_object *cylinder)
{
	t_cylinder	ints;
	int			type;

	ints = init_ints_struct(ray, cylinder);
	compute_cyl_hull(&ints, ray, cylinder);
	compute_cyl_cap(&ints, ray, cylinder);
	type = get_min_positive(ints.d_hull, ints.d_cap);
	if (type == -1)
		return ;
	ray->object = cylinder;
	if (type == 0)
	{
		ray->intersection = ints.d_hull;
		ray->normal = subtract(subtract(get_hitpoint(ray), ints.b),
				multiply(cylinder->direction, ints.t_hull));
		ray->normal = normalize(ray->normal);
		return ;
	}
	ray->intersection = ints.d_cap;
	ray->normal = multiply(cylinder->direction, ints.orientation_cap);
}
