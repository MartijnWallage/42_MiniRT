/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:02:40 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 17:08:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_cylinder_tab(t_build *build)
{
	char		**tab;

	tab = build->tab;
	if (ft_tablen((void **)tab) != 6
		|| !is_vector(build, tab[1])
		|| !is_normal_vector(build, tab[2])
		|| !is_posnum(build, tab[3])
		|| !is_posnum(build, tab[4])
		|| !is_color(build, tab[5]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
}

static t_real	get_cylinder_radius(t_build *build, char *rad)
{
	t_real	ret;

	ret = ft_strtod(build, rad) / 2;
	if (ret <= 0)
		exit_minirt_build(build,
			"cylinder radius must be more than 0", PARSING_EXITCODE);
	return (ret);
}

static t_real	get_cylinder_height(t_build *build, char *height)
{
	t_real	ret;

	ret = ft_strtod(build, height);
	if (ret <= 0)
		exit_minirt_build(build,
			"cylinder height must be more than 0", PARSING_EXITCODE);
	return (ret);
}

void	parse_cylinder(t_build *build)
{
	t_object	*cylinder;
	char		**tab;
	t_scene		*scene;
	t_vec3		right;

	tab = build->tab;
	scene = build->scene;
	check_cylinder_tab(build);
	cylinder = malloc(sizeof(t_object));
	protect_malloc(build, cylinder);
	cylinder->type = CYLINDER;
	cylinder->center = get_vec3(build, tab[1]);
	cylinder->direction = normalize(get_vec3(build, tab[2]));
	cylinder->radius = get_cylinder_radius(build, tab[3]);
	cylinder->height = get_cylinder_height(build, tab[4]);
	cylinder->color = get_color(build, tab[5]);
	right = get_vec3(build, "0,0,1");
	if (norm(cross(right, cylinder->direction)) < EPSILON)
	{
		right.z = 0;
		right.x = -cylinder->direction.z;
	}
	cylinder->up = cross(cylinder->direction, right);
	cylinder->next = scene->objects;
	scene->objects = cylinder;
}
