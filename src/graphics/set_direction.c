/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:28:00 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 17:33:13 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	*set_direction(t_minirt *minirt)
{
	if (minirt->mode == MODE_CAMERA)
		return (&(minirt->scene->camera.direction));
	else if (minirt->mode == MODE_OBJECT)
		return (&(minirt->obj_selected->direction));
	return (NULL);
}

t_vec3	*set_up(t_minirt *minirt)
{
	if (minirt->mode == MODE_CAMERA)
		return (&(minirt->scene->camera.up));
	else if (minirt->mode == MODE_OBJECT)
		return (&(minirt->obj_selected->up));
	return (NULL);
}
