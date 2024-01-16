/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:34 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:39:37 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->objects = NULL;
	scene->spots = NULL;
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_mini_rt	mini_rt;

	// initialisation & parsing
	init_scene(&scene);
	if (argc != 2)
		exit_minirt(&scene, ARGUMENT_ERROR, EXIT_FAILURE);
	parse_scene(argv, &scene);
	print_scene(&scene);
	
	// graphics
	mini_rt.scene = &scene;
	mini_rt.mlx = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT", true);
	if (!mini_rt.mlx)
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	mini_rt.image = mlx_new_image(mini_rt.mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!mini_rt.image)
	{
		mlx_close_window(mini_rt.mlx);
		// free mini_rt.mlx ?
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}

	// display all pixels white
	ft_memset(mini_rt.image->pixels, 255, mini_rt.image->width * mini_rt.image->height * sizeof(int));
	put_circle(mini_rt.image);
	if (mlx_image_to_window(mini_rt.mlx, mini_rt.image, 0, 0) == -1)
	{
		mlx_close_window(mini_rt.mlx);
		// free mini_rt.mlx and mini_rt.image?
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}
	mlx_loop_hook(mini_rt.mlx, &ft_hook, &mini_rt);
	mlx_loop(mini_rt.mlx);
	mlx_terminate(mini_rt.mlx);
	exit_minirt(&scene, NULL, EXIT_SUCCESS);
	return (0);
}
