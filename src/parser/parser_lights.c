/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:35:59 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 17:40:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(t_scene *scene, char *line)
{
	scene->ambient.ratio = ft_strtod(line);
	if (scene->ambient.ratio <= 0.0 || scene->ambient.ratio > 1.0)
		return (0);
	while (*line && *line != ' ')
		line++;
	scene->ambient.color = get_color(scene, line);
	return (1);
}

int	parse_spot(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_ratio(tab[2]))
		return (0);
	scene->spot.source = get_vec3(scene, *++tab);
	scene->spot.ratio = ft_strtod(*++tab);
	return (1);
}
