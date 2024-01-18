/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 14:33:51 by mwallage         ###   ########.fr       */
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
	get_vector(scene, plane->center, *++tab);
	get_vector(scene, plane->normvect, *++tab);
	plane->color = get_color(scene, *++tab);
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
	get_vector(scene, cylinder->center, *++tab);
	get_vector(scene, cylinder->normvect, *++tab);
	cylinder->diameter = ft_strtod(*++tab);
	cylinder->height = ft_strtod(*++tab);
	cylinder->color = get_color(scene, *++tab);
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
	get_vector(scene, sphere->center, *++tab);
	sphere->diameter = ft_strtod(*++tab);
	sphere->color = get_color(scene, *++tab);
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
	get_vector(scene, spot->source, *++tab);
	spot->ratio = ft_strtod(*++tab);
	spot->color = get_color(scene, *++tab);
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
	scene->ambient->color = get_color(scene, *++tab);
}

void	parse_camera(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 4)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	scene->camera = malloc(sizeof(t_camera));
	protect_malloc(scene, NULL, scene->camera);
	get_vector(scene, scene->camera->viewpoint, *++tab);
	get_vector(scene, scene->camera->normvect, *++tab);
	scene->camera->fov = (unsigned char)ft_atoi(*++tab);
	if (scene->camera->fov > 180)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
}