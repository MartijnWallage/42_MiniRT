/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:34 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 13:04:01 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->spot = NULL;
}

static void	init_minirt(t_minirt *minirt, t_scene *scene)
{
	minirt->scene = scene;
	minirt->obj_selected = scene->objects;
	minirt->spot_selected = NULL;
	minirt->scene->camera.up.x = 0;
	minirt->scene->camera.up.y = 1;
	minirt->scene->camera.up.z = 0;
	if (norm(cross(minirt->scene->camera.direction, \
		minirt->scene->camera.up)) < 0.001)
	{
		minirt->scene->camera.up.x = \
			minirt->scene->camera.direction.y;
		minirt->scene->camera.up.y = 0;
		minirt->scene->camera.up.z = 0;
	}
	minirt->mode = MODE_CAMERA;
}

static void	graphics_wrapper(t_minirt *minirt)
{
	mlx_t		*mlx;

	mlx = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT", true);
	if (!mlx)
		exit_minirt(minirt, "MLX failed\n", EXIT_FAILURE);
	minirt->mlx = mlx;
	minirt->image = mlx_new_image(mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!minirt->image || mlx_image_to_window(mlx, minirt->image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
		exit_minirt(minirt, "MLX failed\n", EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, &ft_hook, minirt);
	mlx_loop_hook(mlx, &raytracer, minirt);
	mlx_mouse_hook(mlx, &ft_mousefunc, minirt);
	mlx_resize_hook(mlx, &ft_resizefunc, minirt);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

static void	init_build(t_build *build, t_scene *scene, t_minirt *minirt)
{
	build->tab = NULL;
	build->line = NULL;
	build->fd = 0;
	build->scene = scene;
	build->minirt = minirt;
}
int	main(int argc, char **argv)
{
	t_scene		scene;
	t_minirt	minirt;
	t_build		build;

	init_build(&build, &scene, &minirt);
	init_scene(build.scene);
	if (argc != 2)
		exit_minirt_build(&build, ARGUMENT_ERROR, EXIT_FAILURE);
	parse_scene(argv, &build);
	init_minirt(&minirt, &scene);
	graphics_wrapper(&minirt);
	exit_minirt(&minirt, NULL, EXIT_SUCCESS);
}
