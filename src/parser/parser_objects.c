/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 10:42:21 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_plane(t_build *build)
{
	t_object	*plane;

	if (tablen((void **)build->tab) != 4 || !is_vector(build->tab[1]) || \
		!is_normal_vector(build->tab[2]))
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	plane = malloc(sizeof(t_object));
	protect_malloc(build, plane);
	plane->type = PLANE;
	plane->center = get_vec3(build, build->tab[1]);
	plane->direction = get_vec3(build, build->tab[2]);
	plane->color = get_color(build, build->tab[3]);
	plane->up = get_vec3(build, "0,1,0");
	if (norm(cross(plane->up, plane->direction)) < 0.001)
	{
		plane->up.x = plane->direction.y;
		plane->up.y = 0;
	}
	plane->next = build->scene->objects;
	build->scene->objects = plane;
}

void	parse_cylinder(t_build *build)
{
	t_object	*cylinder;
	char		**tab;
	t_scene		*scene;

	tab = build->tab;
	scene = build->scene;
	if (tablen((void **)tab) != 6 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_posnum(tab[3]) || \
		!is_posnum(tab[4]))
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	cylinder = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, cylinder);
	cylinder->type = CYLINDER;
	cylinder->center = get_vec3(scene, tab[1]);
	cylinder->direction = get_vec3(scene, tab[2]);
	cylinder->radius = ft_strtod(tab[3]) / 2;
	cylinder->height = ft_strtod(tab[4]);
	cylinder->color = get_color(build, tab[5]);
	cylinder->up = get_vec3(build, "0,1,0");
	if (norm(cross(cylinder->up, cylinder->direction)) < 0.001)
	{
		cylinder->up.x = cylinder->direction.y;
		cylinder->up.y = 0;
	}
	cylinder->next = scene->objects;
	scene->objects = cylinder;
}

void	parse_sphere(t_build *build)
{
	t_object	*sphere;
	char		**tab;
	t_scene		*scene;

	tab = build->tab;
	scene = build->scene;
	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_posnum(tab[2]))
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	sphere = malloc(sizeof(t_object));
	protect_malloc(build, sphere);
	sphere->type = SPHERE;
	sphere->center = get_vec3(build, tab[1]);
	sphere->radius = ft_strtod(tab[2]) / 2;
	sphere->color = get_color(build, tab[3]);
	sphere->next = scene->objects;
	scene->objects = sphere;
}
