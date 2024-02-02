/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:31:38 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/26 19:59:15 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calc_plane_intersection(t_ray *ray, t_object *plane)
{
	double	denom;
	double	scalar;

	denom = dot(ray->direction, plane->direction);
	if (fabs(denom) < EPSILON)
		return ;
	scalar = dot(subtract(plane->center, ray->origin), plane->direction)
		/ denom;
	if (scalar <= 0 || (ray->intersection != -1 && scalar > ray->intersection))
		return ;
	ray->object = plane;
	ray->intersection = scalar;
	ray->normal = plane->direction;
	if (dot(ray->direction, plane->direction) > 0)
		ray->normal = multiply(plane->direction, -1);
}

// Calculations following https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
void	calc_sphere_intersection(t_ray *ray, t_object *sphere)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	scalar;
	double	t0;
	double	t1;

	oc = subtract(ray->origin, sphere->center);
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(oc, ray->direction);
	c = dot(oc, oc) - pow2(sphere->radius);
	delta = pow2(b) - 4 * a * c;
	if (delta < 0)
		return ;
	t0 = (-b - sqrt(delta)) / (2.0 * a);
	t1 = (-b + sqrt(delta)) / (2.0 * a);
	if (t0 < t1 && t0 >= 0)
		scalar = t0;
	else
		scalar = t1;
	if (scalar < 0 || (ray->intersection != -1 && scalar > ray->intersection))
		return ;
	ray->intersection = scalar;
	ray->object = sphere;
	ray->normal = normalize(subtract(add(multiply(ray->direction, ray->intersection), ray->origin), sphere->center));
	if (dot(ray->normal, ray->direction) > 0)
		ray->normal = multiply(ray->normal, -1);
}
/* 	double		delta;
	double		b;
	double		c;
	double		temp;
	t_vec3	temp_vec;

	temp_vec = subtract(viewpoint, sphere->center);
	b = 2 * dot(ray->direction, temp_vec);
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
		scalar = t0;
	else
		scalar = t1;
		ray->intersection = temp;
		ray->object = sphere;
	}

int	is_within_range(double nbr, double min, double max)
{
	return (nbr >= min && nbr <= max);
}

double	lowest_within_cylinder(t_ray *ray, t_object *cylinder, double t0, double t1)
{
	double	minY;
	double	maxY;
	double	y0;
	double	y1;

	minY = cylinder->center.y - cylinder->height / 2;		// I think we need matrix transformations to take account of the direction of the cylinder
	maxY = cylinder->center.y + cylinder->height / 2;
	y0 = ray->origin.y + t0 * ray->direction.y;
	y1 = ray->origin.y + t1 * ray->direction.y;
	if (is_within_range(y0, minY, maxY) && is_within_range(y1, minY, maxY))
	{
		if (t0 < t1 && t0 >= 0)
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
*/