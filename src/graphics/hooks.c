/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 13:49:15 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief Set mode of control if key is pressed. If L or O is pressed 
///		multiple times in a row, the next spotlights or object respectively 
///		is selected
/// @param minirt A pointer to struct that contains program parameters
static void	mode_hooks(t_minirt *minirt)
{
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_L) && minirt->scene->spotlights)
	{
		minirt->mode = MODE_SPOT;
		if (minirt->spotlights_selected && minirt->spotlights_selected->next)
			minirt->spotlights_selected = minirt->spotlights_selected->next;
		else
			minirt->spotlights_selected = minirt->scene->spotlights;
	}
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_O))
	{
		minirt->mode = MODE_OBJECT;
		if (minirt->obj_selected && minirt->obj_selected->next)
			minirt->obj_selected = minirt->obj_selected->next;
		else
			minirt->obj_selected = minirt->scene->objects;
	}
}

/// @brief Function that handles keyboard events
/// @param param A pointer to the struct that contains the program data
void	ft_hook(void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(minirt->mlx);
	if (mlx_is_key_down(minirt->mlx, MLX_KEY_C))
		minirt->mode = MODE_CAMERA;
	mode_hooks(minirt);
	translation_hooks(minirt);
	if (minirt->mode != MODE_SPOT)
		rotation_hooks(minirt);
}

/// @brief Function that handles mouse events
/// @param button Pressed button on the mouse
/// @param action Key action of the button
/// @param mods Key modifier, e.g. SHIFT
/// @param param A pointer to the struct that contains the program data
void	ft_mousefunc(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param)
{
	int			x;
	int			y;
	t_minirt	*minirt;
	t_ray		ray;

	minirt = (t_minirt *)param;
	ray.object = NULL;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(minirt->mlx, &x, &y);
		if (x < 0 || x > minirt->mlx->width || y < 0 || y > minirt->mlx->height)
			return ;
		compute_camera_ray(minirt, x, y, &ray);
		compute_ray_object_intersection(minirt, &ray);
		if (ray.object)
		{
			minirt->mode = MODE_OBJECT;
			minirt->obj_selected = ray.object;
		}
		else
			minirt->mode = MODE_CAMERA;
	}
	if (mods == MLX_SHIFT)
		param++;
}

/// @brief Function that gives the event for resizing the window
/// @param width New width of the window
/// @param height New height of the window
/// @param param Struct that contains the program data
void	ft_resizefunc(int width, int height, void *param)
{
	t_minirt	*minirt;
	mlx_t		*mlx;

	minirt = (t_minirt *)param;
	mlx = minirt->mlx;
	mlx_delete_image(mlx, minirt->image);
	minirt->image = mlx_new_image(mlx, width, height);
	if (!minirt->image || mlx_image_to_window(mlx, minirt->image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
		exit_minirt(minirt, "MLX failed\n", EXIT_FAILURE);
	}
}
