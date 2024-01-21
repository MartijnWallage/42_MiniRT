/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 14:30:14 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

void	ft_hook(void *param)
{
	t_minirt	*minirt;
	t_camera	*camera;

	minirt = (t_minirt *)param;
	camera = minirt->scene->camera;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(minirt->mlx);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_LEFT))
		camera->viewpoint.x += TRANSLATION_SPEED;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_RIGHT))
		camera->viewpoint.x -= TRANSLATION_SPEED;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_UP))
		camera->viewpoint.y += TRANSLATION_SPEED;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_DOWN))
		camera->viewpoint.y -= TRANSLATION_SPEED;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_EQUAL))
		camera->viewpoint.z += TRANSLATION_SPEED;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_MINUS))
		camera->viewpoint.z -= TRANSLATION_SPEED;
}

