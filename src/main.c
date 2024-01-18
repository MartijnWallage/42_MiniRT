/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:34 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 15:58:06 by mwallage         ###   ########.fr       */
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

void	print_scene(t_scene *scene)
{
	printf("\n****************************\n");
	printf("\nCAMERA:\n");
	printf("Fov: \t\t%d\n", scene->camera->fov);
	printf("Viewpoint: %lf, %lf, %lf\n",
		scene->camera->viewpoint[0],
		scene->camera->viewpoint[1], 
		scene->camera->viewpoint[2]);
	printf("Norm vector: %lf, %lf, %lf\n",
		scene->camera->normvect[0],
		scene->camera->normvect[1],
		scene->camera->normvect[2]);
	printf("\nAMBIENT LIGHT:\n");
	printf("Ratio: %f\n", scene->ambient->ratio);
	printf("color: %x\n",
		scene->ambient->color);
	printf("\nSPOT LIGHTS:\n");
	t_spot	*curr = scene->spots;
	while (curr)
	{
		printf("\nRatio: %f\n", curr->ratio);
		printf("color: %x\n", curr->color);
		printf("Source: %lf, %lf, %lf\n",
			curr->source[0],
			curr->source[1],
			curr->source[2]);
		curr = curr->next;
	}
	printf("\nOBJECTS:\n");
	t_object	*curr2 = scene->objects;
	while (curr2)
	{
		printf("\nType: %d\n", curr2->type);
		printf("Center: %lf, %lf, %lf\n",
			curr2->center[0],
			curr2->center[1],
			curr2->center[2]);
		printf("Color: %x\n", curr2->color);
		printf("Norm vector: %lf, %lf, %lf\n",
			curr2->normvect[0],
			curr2->normvect[1],
			curr2->normvect[2]);
		printf("Diameter: %lf\n",
			curr2->diameter);
		printf("Height: %lf\n",
			curr2->height);
		curr2 = curr2->next;
	}
	printf("*****************************\n");
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
