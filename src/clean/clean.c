/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:50:01 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 15:50:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_objects_array(t_object **objects)
{
	int	i;

	i = 0;
	while (objects[i])
		free(objects[i++]);
	free(objects);
}

void	free_spots_array(t_light **spots)
{
	int	i;

	i = 0;
	while (spots[i])
		free(spots[i++]);
	free(spots);
}

void	exit_minirt(t_scene *scene, char *message, int status)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->objects)
		free_objects_array(scene->objects);
	if (scene->spots)
		free_spots_array(scene->spots);
	if (status == EXIT_FAILURE)
		printf("%s", message);
	exit(status);
}
