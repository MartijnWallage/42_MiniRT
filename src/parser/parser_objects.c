/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/17 19:02:55 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_plane(t_scene *scene, char **tab)
{
	t_object	*plane;
	
	if (tablen((void **)tab) != 4)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	plane = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, plane);
	plane->type = PLANE;
	get_vector(plane->center, *++tab);
	get_vector(plane->normvect, *++tab);
	get_color(plane->color, *++tab);
	plane->next = scene->objects;
	scene->objects = plane;
}

void	parse_cylinder(t_scene *scene, char **tab)
{
	t_object	*cylinder;

	if (tablen((void **)tab) != 6)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	cylinder = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, cylinder);
	cylinder->type = CYLINDER;
	get_vector(cylinder->center, *++tab);
	get_vector(cylinder->normvect, *++tab);
	cylinder->diameter = ft_strtod(*++tab);
	cylinder->height = ft_strtod(*++tab);
	get_color(cylinder->color, *++tab);
	cylinder->next = scene->objects;
	scene->objects = cylinder;
}

void	parse_sphere(t_scene *scene, char **tab)
{
	t_object	*sphere;

	if (tablen((void **)tab) != 4)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	sphere = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, sphere);
	sphere->type = SPHERE;
	get_vector(sphere->center, *++tab);
	sphere->diameter = ft_strtod(*++tab);
	get_color(sphere->color, *++tab);
	sphere->next = scene->objects;
	scene->objects = sphere;
}

void	parse_spot(t_scene *scene, char **tab)
{
	t_spot	*spot;
	
	if (tablen((void **)tab) != 4)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	spot = malloc(sizeof(t_spot));
	protect_malloc(scene, NULL, spot);
	get_vector(spot->source, *++tab);
	spot->ratio = ft_strtod(*++tab);
	get_color(scene->ambient->color, *++tab);
	spot->next = scene->spots;
	scene->spots = spot;
}

void	parse_ambient(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 3)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	scene->ambient = malloc(sizeof(t_ambient));
	protect_malloc(scene, NULL, scene->ambient);
	scene->ambient->ratio = ft_strtod(*++tab);
	get_color(scene->ambient->color, *++tab);
}

void	parse_camera(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 4)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	scene->camera = malloc(sizeof(t_camera));
	protect_malloc(scene, NULL, scene->camera);
	get_vector(scene->camera->viewpoint, *++tab);
	get_vector(scene->camera->normvect, *++tab);
	scene->camera->fov = (unsigned char)ft_atoi(*++tab);
}