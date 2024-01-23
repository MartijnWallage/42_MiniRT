/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:34 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 13:13:26 by mwallage         ###   ########.fr       */
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
	t_minirt	minirt;

	// initialisation & parsing
	init_scene(&scene);
	if (argc != 2)
		exit_minirt(&scene, ARGUMENT_ERROR, EXIT_FAILURE);
	parse_scene(argv, &scene);
//	print_scene(&scene);

	// Only as proof of concept for rotation
	minirt.selected = scene.objects;
	while (scene.objects && scene.objects->type != CYLINDER)
		(minirt.selected)++;
	if (scene.objects->type != CYLINDER)
		minirt.selected = NULL;
	// graphics
	minirt.scene = &scene;
	minirt.mlx = mlx_init(IMAGE_WIDTH, IMAGE_HEIGHT, "miniRT", true);
	if (!minirt.mlx)
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	minirt.image = mlx_new_image(minirt.mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!minirt.image)
	{
		mlx_close_window(minirt.mlx);
		mlx_terminate(minirt.mlx);
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}

	//	Raytracer

	/*	
		The Raytracer returns an image on the basis of the scene.
		
		raytracer(minirt.image, minirt.scene);

		Determine four corner vectors
		Loop through the image
		For each pixel: calculate the corresponding ray vector. 
			Loop through all objects. 
				For each object: calculate intersections with current ray, only store the closest one.				
			Calculate colour of current pixel.

	*/
	raytracer(&minirt);
	if (mlx_image_to_window(minirt.mlx, minirt.image, 0, 0) == -1)
	{
		mlx_close_window(minirt.mlx);
		mlx_terminate(minirt.mlx);
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}
	mlx_loop_hook(minirt.mlx, &ft_hook, &minirt);
	mlx_loop_hook(minirt.mlx, &raytracer, &minirt);
	mlx_loop(minirt.mlx);
	mlx_terminate(minirt.mlx);
	exit_minirt(&scene, NULL, EXIT_SUCCESS);
	return (0);
}
