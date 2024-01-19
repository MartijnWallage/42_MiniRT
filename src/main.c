/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:34 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/19 14:04:46 by mwallage         ###   ########.fr       */
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
		mlx_terminate(mini_rt.mlx);
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}

	//	Raytracer

	/*	
		The Raytracer returns an image on the basis of the scene.
		
		raytracer(mini_rt.image, mini_rt.scene);

		Determine four corner vectors
		Loop through the image
		For each pixel: calculate the corresponding ray vector. 
			Loop through all objects. 
				For each object: calculate intersections with current ray, only store the closest one.				
			Calculate colour of current pixel.

	*/


	// display all pixels white
	ft_memset(mini_rt.image->pixels, 255, mini_rt.image->width * mini_rt.image->height * sizeof(int));
	put_circle(mini_rt.image);
	if (mlx_image_to_window(mini_rt.mlx, mini_rt.image, 0, 0) == -1)
	{
		mlx_close_window(mini_rt.mlx);
		mlx_terminate(mini_rt.mlx);
		exit_minirt(&scene, "MLX failed\n", EXIT_FAILURE);
	}
	mlx_loop_hook(mini_rt.mlx, &ft_hook, &mini_rt);
	mlx_loop(mini_rt.mlx);
	mlx_terminate(mini_rt.mlx);
	exit_minirt(&scene, NULL, EXIT_SUCCESS);
	return (0);
}
