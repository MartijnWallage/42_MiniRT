/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:41 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/26 18:48:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_camera(t_build *build)
{
	if (ft_tablen((void **)build->tab) != 4
		|| !is_vector(build, build->tab[1])
		|| !is_vector(build, build->tab[2])
		|| !is_angle(build, build->tab[3]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
	build->scene->camera.viewpoint = get_vec3(build, build->tab[1]);
	build->scene->camera.direction = normalize(get_vec3(build, build->tab[2]));
	build->scene->camera.fov = get_real(build, build->tab[3]);
	build->scene->camera.fov *= M_PI / 180;
	return (1);
}
