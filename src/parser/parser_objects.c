/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/16 14:11:28 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	add_object(t_scene *scene, t_object *object)
{
	if (scene->objects == NULL)
	{
		scene->objects = malloc(sizeof(t_object **) * 2);
		scene->objects[0] = NULL;
		scene->objects[1] = NULL;
	}
	protect_malloc(scene, NULL, scene->objects);
	while (scene->objects)
		scene->objects++;
	*scene->objects = object;
}

void	parse_plane(t_scene *scene, char **columns)
{
	t_object	*plane;

	plane = malloc(sizeof(t_object*));
	plane->type = PLANE;
	plane->center = get_vector(columns(1));
	plane->normvect = get_vector(columns(2));
	plane->color = get_color(columns[3]);
	add_object(scene, plane);
}

void	parse_cylinder(t_scene *scene, char **columns)
{

}

void	parse_sphere(t_scene *scene, char **columns)
{

}