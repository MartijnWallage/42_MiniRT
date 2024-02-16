/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:38:51 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 18:23:31 by mwallage         ###   ########.fr       */
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
