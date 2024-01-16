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

void	print_scene(t_scene *scene)
{
	printf("AMBIENT LIGHT:\n");
	printf("Ratio: %lf\n", scene->ambient->ratio);
	printf("Colour: %lf, %lf, %lf\n",
		scene->ambient->colour[0],
		scene->ambient->colour[1], 
		scene->ambient->colour[2]);
	printf("Source: %lf, %lf, %lf\n",
		scene->ambient->source[0],
		scene->ambient->source[1],
		scene->ambient->source[2]);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	init_scene(&scene);
	if (argc != 2)
		exit_minirt(&scene, ARGUMENT_ERROR, EXIT_FAILURE);
	parse_scene(argv, &scene);
	print_scene(&scene);
	exit_minirt(&scene, NULL, EXIT_SUCCESS);
	return (0);
}
