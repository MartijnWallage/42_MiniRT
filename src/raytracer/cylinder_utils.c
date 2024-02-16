/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:38:51 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 13:49:02 by mwallage         ###   ########.fr       */
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

int	get_min_positive(t_real value1, t_real value2)
{
	if (value1 < 0 && value2 < 0)
		return (-1);
	else if (value1 < 0 && value2 > 0)
		return (1);
	else if (value2 < 0 && value1 > 0)
		return (0);
	else if (value1 <= value2)
		return (0);
	else if (value2 < value1)
		return (1);
	return (-1);
}
