/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:38:51 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/17 07:56:30 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cylinder	init_ints_struct(t_ray	*ray, t_object *cylinder)
{
	t_cylinder	ints;

	ints.nxa = cross(ray->direction, cylinder->direction);
	ints.b = subtract(cylinder->center, ray->origin);
	ints.b_x_a = cross(ints.b, cylinder->direction);
	ints.d_cap = -1;
	ints.d_hull = -1;
	return (ints);
}

int	get_min_positive(t_real value0, t_real value1)
{
	if (value0 >= 0 && (value1 < 0 || value0 <= value1))
		return (0);
	if (value1 >= 0)
		return (1);
	return (-1);
}

int	is_first_visible(t_real a, t_real b, t_real scalar)
{
	if (a < 0 || (scalar != -1 && a > scalar))
		return (0);
	return (b < 0 || a <= b);
}
