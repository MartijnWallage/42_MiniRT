/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:35:59 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 13:03:15 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_ambient(t_build *build)
{
	t_scene	*scene;

	if (tablen((void **)build->tab) != 3)
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	scene = build->scene;
	scene->ambient.ratio = ft_strtod(build->tab[1]);
	if (scene->ambient.ratio <= 0.0)
		exit_minirt_build(build, "'Objects are never completely in the dark'", PARSING_EXITCODE);
	if (scene->ambient.ratio > 1.0)
		exit_minirt_build(build, "Ambient ratio must be <= 1.0", PARSING_EXITCODE);
	scene->ambient.color = get_color(build, build->tab[2]);
}

void	parse_spot(t_build *build)
{
	if (tablen((void **)build->tab) != 4 || !is_vector(build, build->tab[1]) || \
		!is_ratio(build->tab[2]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	build->scene->spot = malloc(sizeof(t_spot));
	protect_malloc(build, build->scene->spot);
	build->scene->spot->source = get_vec3(build, build->tab[1]);
	build->scene->spot->ratio = ft_strtod(build->tab[2]);
}
