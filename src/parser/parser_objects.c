/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 17:06:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_plane(t_scene *scene, char **tab, int fd)
{
	t_object	*plane;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]))
		return (0);
	plane = malloc(sizeof(t_object));
	protect_malloc(plane, scene, NULL, fd);
	plane->type = PLANE;
	plane->center = get_vec3(scene, *++tab);
	plane->direction = get_vec3(scene, *++tab);
	plane->color = get_color(scene, *++tab, fd);
	plane->up = get_vec3(scene, "0,1,0");
	if (norm(cross(plane->up, plane->direction)) < 0.001)
	{
		plane->up.x = plane->direction.y;
		plane->up.y = 0;
	}
	plane->next = scene->objects;
	scene->objects = plane;
	return (1);
}

int	parse_cylinder(t_scene *scene, char **tab, int fd)
{
	t_object	*cylinder;

	if (tablen((void **)tab) != 6 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_posnum(tab[3]) || \
		!is_posnum(tab[4]))
		return (0);
	cylinder = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, cylinder);
	cylinder->type = CYLINDER;
	cylinder->center = get_vec3(scene, *++tab);
	cylinder->direction = get_vec3(scene, *++tab);
	cylinder->radius = ft_strtod(*++tab) / 2;
	cylinder->height = ft_strtod(*++tab);
	cylinder->color = get_color(scene, *++tab, fd);
	cylinder->up = get_vec3(scene, "0,1,0");
	if (norm(cross(cylinder->up, cylinder->direction)) < 0.001)
	{
		cylinder->up.x = cylinder->direction.y;
		cylinder->up.y = 0;
	}
	cylinder->next = scene->objects;
	scene->objects = cylinder;
	return (1);
}

int	parse_sphere(t_scene *scene, char **tab, int fd)
{
	t_object	*sphere;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_posnum(tab[2]))
		return (0);
	sphere = malloc(sizeof(t_object));
	protect_malloc(scene, NULL, sphere);
	sphere->type = SPHERE;
	sphere->center = get_vec3(scene, *++tab);
	sphere->radius = ft_strtod(*++tab) / 2;
	sphere->color = get_color(scene, *++tab, fd);
	sphere->next = scene->objects;
	scene->objects = sphere;
	return (1);
}
