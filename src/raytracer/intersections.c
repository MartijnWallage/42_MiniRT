/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:31:38 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 12:23:53 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	calc_plane_intersection(t_ray *ray, t_object *plane)
{
	t_real	denom;
	t_real	scalar;

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

void	calc_sphere_intersection(t_ray *ray, t_object *sphere)
{
	t_vec3	oc;
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	delta;
	t_real	scalar;
	t_real	t0;
	t_real	t1;

	oc = subtract(ray->origin, sphere->center);
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(oc, ray->direction);
	c = dot(oc, oc) - pow2(sphere->radius);
	delta = pow2(b) - 4 * a * c;
	if (delta < EPSILON)
		return ;
	t0 = (-b - sqrt(delta)) / (2.0 * a);
	t1 = (-b + sqrt(delta)) / (2.0 * a);
	if (t0 < t1 && t0 >= EPSILON)
		scalar = t0;
	else
		scalar = t1;
	if (scalar < EPSILON || (ray->intersection != -1 && scalar > ray->intersection))
		return ;
	ray->intersection = scalar;
	ray->object = sphere;
	ray->normal = multiply(ray->direction, ray->intersection);
	ray->normal = add(ray->normal, ray->origin);
	ray->normal = normalize(subtract(ray->normal, sphere->center));
	if (dot(ray->normal, ray->direction) > 0)
		ray->normal = multiply(ray->normal, -1);
}
