/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cyl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:02:40 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/16 17:08:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_cyl_tab(t_build *build)
{
	char		**tab;

	tab = build->tab;
	if (ft_tablen((void **)tab) != 6 + 2 * BONUS
		|| !is_vector(build, tab[1])
		|| !is_normal_vector(build, tab[2])
		|| !is_posnum(build, tab[3])
		|| !is_posnum(build, tab[4])
		|| !is_color(build, tab[5])
		|| (BONUS
			&& (!is_real(build->tab[6])
				|| !is_real(build->tab[7]))))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
}

static t_real	get_cyl_radius(t_build *build, char *rad)
{
	t_real	ret;

	ret = get_real(build, rad) / 2;
	if (ret <= 0)
		exit_minirt_build(build,
			"cyl radius must be more than 0", PARSING_EXITCODE);
	return (ret);
}

static t_real	get_cyl_height(t_build *build, char *height)
{
	t_real	ret;

	ret = get_real(build, height);
	if (ret <= 0)
		exit_minirt_build(build,
			"cyl height must be more than 0", PARSING_EXITCODE);
	return (ret);
}

void	parse_cyl(t_build *build)
{
	t_object	*cyl;
	char		**tab;
	t_scene		*scene;
	t_vec3		right;

	tab = build->tab;
	scene = build->scene;
	check_cyl_tab(build);
	cyl = malloc(sizeof(t_object));
	protect_malloc(build, cyl);
	cyl->type = CYLINDER;
	cyl->center = get_vec3(build, tab[1]);
	cyl->direction = normalize(get_vec3(build, tab[2]));
	cyl->radius = get_cyl_radius(build, tab[3]);
	cyl->height = get_cyl_height(build, tab[4]);
	cyl->color = get_color(build, tab[5]);
	right = get_vec3(build, "0,0,1");
	if (norm(cross(right, cyl->direction)) < EPSILON)
	{
		right.z = 0;
		right.x = -cyl->direction.z;
	}
	cyl->up = cross(cyl->direction, right);
	cyl->diffuse = 1.0;
	cyl->shininess = 0.0;
	if (BONUS)
	{
		cyl->diffuse = get_real(build, tab[6]);
		cyl->shininess = get_real(build, tab[7]);
	}
	cyl->next = scene->objects;
	scene->objects = cyl;
}
