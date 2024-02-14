/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:41 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 13:54:05 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_camera(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_angle(tab[3]))
		return (0);
	scene->camera = malloc(sizeof(t_camera));
	protect_malloc(scene, NULL, scene->camera);
	scene->camera->viewpoint = get_vec3(scene, tab[1]);
	scene->camera->direction = normalize(get_vec3(scene, tab[2]));
	scene->camera->fov = ft_strtod(tab[3]);
	return (1);
}
