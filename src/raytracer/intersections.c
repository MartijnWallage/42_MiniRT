/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:31:38 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 16:21:02 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calc_plane_intersection(t_ray *ray, t_object *plane, t_vec3 viewpoint)
{
	double	denom;
	double	scalar;

	denom = dot(ray->normvect, plane->normvect);
	if (fabs(denom) < EPSILON)
		return ;
	scalar = dot(subtract(plane->center, viewpoint), plane->normvect)
		/ denom;
	if (scalar <= 0 || (ray->intersection != -1 && scalar > ray->intersection))
		return ;
	ray->object = plane;
	ray->intersection = scalar;
}

// Calculations following https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
void	calc_sphere_intersection(t_ray *ray, t_object *sphere, t_vec3 viewpoint)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	scalar;

	oc = subtract(viewpoint, sphere->center);
	a = dot(ray->normvect, ray->normvect);
	b = 2.0 * dot(oc, ray->normvect);
	c = dot(oc, oc) - pow2(sphere->radius);
	delta = pow2(b) - 4 * a * c;
	if (delta < 0)		// compare to below. Is this correct?
		return ;
	scalar = (-b - sqrt(delta)) / (2.0 * a);
	if (ray->intersection != -1 && scalar > ray->intersection)
		return ;
	ray->intersection = scalar;
	ray->object = sphere;
/* 	double		delta;
	double		b;
	double		c;
	double		temp;
	t_vec3	temp_vec;

	temp_vec = subtract(viewpoint, sphere->center);
	b = 2 * dot(ray->normvect, temp_vec);
	temp = norm(temp_vec);
	c = pow2(temp) - sphere->radius * sphere->radius;
	delta = pow2(b) - 4 * c;
	if (delta < 0)
		return ;
	else if (delta < EPSILON)
		temp = -b / 2;
	else
	{
		delta = sqrt(delta);
		temp = ft_min_positive((-b + delta) / 2, (-b - delta) / 2);
	}
	if (temp > 0)
	{
		ray->intersection = temp;
		ray->object = sphere;
	} */
}

int	is_within_range(double nbr, double min, double max)
{
	return (nbr >= min && nbr <= max);
}

double	lowest_within_cylinder(t_ray *ray, t_object *cylinder, t_vec3 viewpoint, double t0, double t1)
{
	double	minY;
	double	maxY;
	double	y0;
	double	y1;

	minY = cylinder->center.y;
	maxY = cylinder->center.y + cylinder->height;
	y0 = viewpoint.y + t0 * ray->normvect.y;
	y1 = viewpoint.y + t1 * ray->normvect.y;
	if (is_within_range(y0, minY, maxY) && is_within_range(y1, minY, maxY))
	{
		if (t0 < t1)
			return (t0);
		else
			return (t1);
	}
	if (is_within_range(y0, minY, maxY))
		return (t0);
	if (is_within_range(y1, minY, maxY))
		return (t1);
	return (0);
}

// Calculations following https://en.wikipedia.org/wiki/Line-cylinder_intersection
void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder, t_vec3 viewpoint)
{
	t_vec3	origin_to_center;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t0;
	double	t1;
	double	scalar;

	origin_to_center = subtract(viewpoint, cylinder->center);
	a = pow2(ray->normvect.x) + pow2(ray->normvect.z);
	b = 2.0 * (origin_to_center.x * ray->normvect.x + origin_to_center.z * ray->normvect.z);
	c = pow2(origin_to_center.x) + pow2(origin_to_center.z) - pow2(cylinder->radius);
	delta = pow2(b) - 4 * a * c;
	if (delta < 0)
		return ;
	t0 = (-b - sqrt(delta)) / (2.0 * a);
	t1 = (-b + sqrt(delta)) / (2.0 * a);
	scalar = lowest_within_cylinder(ray, cylinder, viewpoint, t0, t1);
	if (scalar == 0 || (ray->intersection != -1 && scalar > ray->intersection))
		return ;
	ray->object = cylinder;
	ray->intersection = scalar;
/* 	t_vec3	n_x_a;
	t_vec3	b_x_a;
	t_vec3	b;
	t_vec3	temp;
	double		norm_temp;
	double		dot_temp;
	double		delta;
	double		t1;
	double		t2;
	double		d1;
	double		d2;
	double		d_final;

	n_x_a = cross(ray->normvect, cylinder->normvect);
	b = subtract(cylinder->center, viewpoint);
	norm_temp = norm(n_x_a);
	if (norm_temp < EPSILON)
		return ;
	delta = dot(n_x_a, n_x_a) * pow2(cylinder->radius) - \
		pow2(dot(b, n_x_a));
	if (delta < 0)
		return ;
	b_x_a = cross(b, cylinder->normvect);
	dot_temp = dot(n_x_a, b_x_a);
	d1 = (dot_temp + sqrt(delta)) / pow2(norm_temp);
	temp = subtract(multiply(ray->normvect, d1), b);
	t1 = dot(cylinder->normvect, temp);
	d2 = (dot_temp - sqrt(delta)) / pow2(norm_temp);
	temp = subtract(multiply(ray->normvect, d2), b);
	t2 = dot(cylinder->normvect, temp);
	if (t1 < - cylinder->height / 2 || t1 > cylinder->height / 2 )
		d1 = -1;
	if (t2 < - cylinder->height / 2 || t2 > cylinder->height / 2 )
		d2 = -1;
	d_final = ft_min_positive(d1, d2);
	if (d_final >= 0 && (ray->intersection < 0 || d_final < ray->intersection))
	{
		ray->object = cylinder;
		ray->intersection = d_final;
	}
	return ; */
}
