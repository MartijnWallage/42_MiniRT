/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/26 18:51:06 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_plane_tabs(t_build *build)
{
	if (ft_tablen((void **)build->tab) != 6)
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_vector(build, build->tab[1]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_vector(build, build->tab[2]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_color(build, build->tab[3]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_ratio(build, build->tab[4]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_posnum(build, build->tab[5]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
}

void	parse_plane(t_build *build)
{
	t_object	*plane;

	check_plane_tabs(build);
	plane = malloc(sizeof(t_object));
	protect_malloc(build, plane);
	plane->type = PLANE;
	plane->center = get_vec3(build, build->tab[1]);
	plane->direction = normalize(get_vec3(build, build->tab[2]));
	plane->color = get_color(build, build->tab[3]);
	plane->up = get_vec3(build, "0,1,0");
	if (norm(cross(plane->up, plane->direction)) < 0.001)
	{
		plane->up.x = plane->direction.y;
		plane->up.y = 0;
	}
	plane->diffuse = 1.0;
	plane->shininess = 0.0;
	plane->diffuse = get_real(build, build->tab[4]);
	plane->shininess = get_real(build, build->tab[5]);
	plane->next = build->scene->objects;
	build->scene->objects = plane;
}

static void	check_sphere_tabs(t_build *build)
{
	char	**tab;

	tab = build->tab;
	if (ft_tablen((void **)tab) != 6)
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_vector(build, tab[1]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_posnum(build, tab[2]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_color(build, tab[3]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_ratio(build, build->tab[4]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	if (!is_posnum(build, build->tab[5]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
}

void	parse_sphere(t_build *build)
{
	t_object	*sphere;
	char		**tab;

	check_sphere_tabs(build);
	tab = build->tab;
	sphere = malloc(sizeof(t_object));
	protect_malloc(build, sphere);
	sphere->type = SPHERE;
	sphere->center = get_vec3(build, build->tab[1]);
	sphere->radius = get_real(build, build->tab[2]) / 2;
	if (sphere->radius <= 0)
		exit_minirt_build(build,
			"radius must be more than 0", PARSING_EXITCODE);
	sphere->color = get_color(build, tab[3]);
	sphere->diffuse = 1.0;
	sphere->shininess = 0.0;
	sphere->diffuse = get_real(build, build->tab[4]);
	sphere->shininess = get_real(build, build->tab[5]);
	sphere->next = build->scene->objects;
	build->scene->objects = sphere;
}
