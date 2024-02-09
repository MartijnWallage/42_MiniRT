/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/22 14:28:54 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_plane(t_scene *scene, char **tab)
{
	t_object	*plane;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_color_vector(tab[3]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	plane = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, plane);
	plane->type = PLANE;
	plane->center = get_vec3(scene, *++tab);
	plane->direction = normalize(get_vec3(scene, *++tab));	// easier for testing to already normalize, maybe change back later
	plane->color = get_color(scene, *++tab);
	plane->up = get_vec3(scene, "0,1,0");
	if (norm(cross(plane->up, plane->direction)) < 0.001)
	{
		plane->up.x = plane->direction.y;
		plane->up.y = 0;
	}
	plane->next = scene->objects;
	scene->objects = plane;
}

void	parse_cylinder(t_scene *scene, char **tab)
{
	t_object	*cylinder;

	if (tablen((void **)tab) != 6 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_posnum(tab[3]) || \
		!is_posnum(tab[4]) || !is_color_vector(tab[5]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	cylinder = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, cylinder);
	cylinder->type = CYLINDER;
	cylinder->center = get_vec3(scene, *++tab);
	cylinder->direction = normalize(get_vec3(scene, *++tab));
	cylinder->radius = ft_strtod(*++tab) / 2;
	cylinder->height = ft_strtod(*++tab);
	cylinder->color = get_color(scene, *++tab);
	cylinder->up = get_vec3(scene, "0,1,0");
	if (norm(cross(cylinder->up, cylinder->direction)) < 0.001)
	{
		cylinder->up.x = cylinder->direction.y;
		cylinder->up.y = 0;
	}
	cylinder->next = scene->objects;
	scene->objects = cylinder;
}

void	parse_sphere(t_scene *scene, char **tab)
{
	t_object	*sphere;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_posnum(tab[2]) || !is_color_vector(tab[3]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	sphere = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, sphere);
	sphere->type = SPHERE;
	sphere->center = get_vec3(scene, *++tab);
	sphere->radius = ft_strtod(*++tab) / 2;
	sphere->color = get_color(scene, *++tab);
	sphere->next = scene->objects;
	scene->objects = sphere;
}
