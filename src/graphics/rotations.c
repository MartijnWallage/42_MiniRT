/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:52:58 by thofting          #+#    #+#             */
/*   Updated: 2024/02/16 11:51:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief Rotate a 3D vector around a specified axis by a given angle.
///
/// The computations are following https://math.stackexchange.com/
///	questions/511370/how-to-rotate-one-vector-about-another .
///
/// @param vector The 3D vector to be rotated.
/// @param axis The axis of rotation.
/// @param angle The angle of rotation in radians.
/// @return The rotated 3D vector.
static t_vec3	rotate_around_axis(t_vec3 vector, t_vec3 axis, t_real angle)
{
	t_vec3	parallel;
	t_vec3	orthogonal;
	t_vec3	product;
	t_vec3	rotated;
	t_real	sin_part;

	parallel = multiply(axis, dot(vector, axis));
	orthogonal = subtract(vector, parallel);
	product = cross(axis, orthogonal);
	sin_part = sin(angle) * norm(orthogonal) / norm(product);
	rotated = add(multiply(orthogonal, cos(angle)), \
		multiply(product, sin_part));
	return (normalize(add(rotated, parallel)));
}

/// @brief Function performs a roll of a target
///
/// This is archieved by rotating the 'up' vector around 
///	the 'direction' vector with a specified angle.
///
/// @param direction Front orientation vactor of a target
/// @param up Upper orientation vector of a target
/// @param angle The angle of roll rotation in radians.
static void	roll_rotation(t_vec3 *direction, t_vec3 *up, t_real angle)
{
	*up = rotate_around_axis(*up, *direction, angle);
}

/// @brief Function performs a yaw of a target
///
/// This is done by rotating the 'direction' vector around 
///	the 'up' vector with a specified angle.
///
/// @param direction Front orientation vactor of a target
/// @param up Upper orientation vector of a target
/// @param angle The angle of yaw rotation in radians.
static void	yaw_rotation(t_vec3 *direction, t_vec3 *up, t_real angle)
{
	*direction = rotate_around_axis(*direction, *up, angle);
}

/// @brief Perform pitch rotation around a given direction.
///
/// 'direction' as well as 'up' are updated by calculating first the 
///	rectangular vector 'right' and then rotating both around it
///
/// @param direction Front orientation vactor of a target
/// @param up Upper orientation vector of a target
/// @param angle The angle of pitch rotation in radians.
static void	pitch_rotation(t_vec3 *direction, t_vec3 *up, t_real angle)
{
	t_vec3	right;

	right = cross(*direction, *up);
	*direction = rotate_around_axis(*direction, right, angle);
	*up = rotate_around_axis(*up, right, angle);
}

/// @brief Rotate orientation of selected object if keys are pressed
/// @param minirt struct that contains program data
void	rotation_hooks(t_minirt *minirt)
{
	t_vec3	*direction;
	t_vec3	*up;

	if (minirt->mode == MODE_CAMERA)
	{
		direction = &(minirt->scene->camera.direction);
		up = &(minirt->scene->camera.up);
	}
	else if (minirt->mode == MODE_OBJECT)
	{
		direction = &(minirt->obj_selected->direction);
		up = &(minirt->obj_selected->up);
	}
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_A))
		roll_rotation(direction, up, ROTATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_D))
		roll_rotation(direction, up, -ROTATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_W))
		pitch_rotation(direction, up, ROTATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_S))
		pitch_rotation(direction, up, -ROTATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_Q))
		yaw_rotation(direction, up, ROTATION_SPEED);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_E))
		yaw_rotation(direction, up, -ROTATION_SPEED);
}
