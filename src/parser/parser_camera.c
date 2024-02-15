/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:41 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 10:23:47 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_camera(t_build *build)
{
	if (tablen((void **)build->tab) != 4 || !is_vector(build->tab[1]) || \
		!is_normal_vector(build->tab[2]) || !is_angle(build->tab[3]))
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	build->scene->camera.viewpoint = get_vec3(build, build->tab[1]);
	build->scene->camera.direction = get_vec3(build, build->tab[2]);
	build->scene->camera.fov = ft_strtod(build->tab[3]);
}
