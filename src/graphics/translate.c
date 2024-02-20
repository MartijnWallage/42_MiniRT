/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:49:24 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 15:10:37 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	translate(t_vec3 *position, t_vec3 *direction, t_real scale)
{
	t_vec3	ret;

	ret = multiply(*direction, scale);
	ret = add(*position, ret);
	return (ret);
}

t_vec3	*set_position(t_minirt *minirt)
{
	if (minirt->mode == MODE_CAMERA)
		return (&(minirt->scene->camera.viewpoint));
	else if (minirt->mode == MODE_OBJECT)
		return (&(minirt->obj_selected->center));
	else if (minirt->mode == MODE_SPOT)
		return (&(minirt->spotlights_selected->source));
	else
		return (NULL);
}

/// @brief Adapt position of selected object if keys are pressed
/// @param minirt A pointer to struct that contains program parameters
void	translation_hooks(t_minirt *minirt)
{
	t_vec3		*position;
	t_camera	*camera;
	t_vec3		right;

	position = set_position(minirt);
	if (!position)
		return ;
	camera = &minirt->scene->camera;
	right = cross(camera->direction, camera->up);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_LEFT))
		*position = translate(position, &right, -TRANSLATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_RIGHT))
		*position = translate(position, &right, TRANSLATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_UP))
		*position = translate(position, &camera->up, TRANSLATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_DOWN))
		*position = translate(position, &camera->up, -TRANSLATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_EQUAL))
		*position = translate(position, &camera->direction, TRANSLATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_MINUS))
		*position = translate(position, &camera->direction, -TRANSLATION_SPEED);
}
