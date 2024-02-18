/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:35:59 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/18 11:56:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(t_build *build)
{
	t_scene	*scene;

	if (ft_tablen((void **)build->tab) != 3 || !is_ratio(build, build->tab[1])
		|| !is_color(build, build->tab[2]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	scene = build->scene;
	scene->ambient.ratio = ft_strtod(build, build->tab[1]);
	if (scene->ambient.ratio <= 0.0)
		exit_minirt_build(build,
			"parsing: objects need light", PARSING_EXITCODE);
	scene->ambient.color = get_color(build, build->tab[2]);
	return (1);
}

void	parse_spotlights(t_build *build)
{
	t_spotlight	*new_light;

	if (ft_tablen((void **)build->tab) != 4
		|| !is_vector(build, build->tab[1])
		|| !is_ratio(build, build->tab[2])
		|| !is_color(build, build->tab[3])
		|| (!CHECK_BONUS && build->scene->spotlights))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	new_light = malloc(sizeof(t_spotlight));
	protect_malloc(build, new_light);
	new_light->source = get_vec3(build, build->tab[1]);
	new_light->ratio = ft_strtod(build, build->tab[2]);
	if (new_light->ratio <= 0)
		exit_minirt_build(build,
			"parsing: spotlight needs brightness", PARSING_EXITCODE);
	new_light->color = 0xFFFFFFFF;
	if (CHECK_BONUS)
		new_light->color = get_color(build, build->tab[3]);
	new_light->next = build->scene->spotlights;
	build->scene->spotlights = new_light;
}
