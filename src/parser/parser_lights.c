/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:35:59 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 13:54:34 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 3 || !is_ratio(tab[1]) || \
		!is_color_vector(tab[2]))
		return (0);
	scene->ambient = malloc(sizeof(t_ambient));
	protect_malloc(scene, NULL, scene->ambient);
	scene->ambient->ratio = ft_strtod(tab[1]);
	scene->ambient->color = get_color(scene, tab[2]);
	return (1);	
}

int	parse_spot(t_scene *scene, char **tab)
{
	t_spot	*spot;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_ratio(tab[2]) || !is_color_vector(tab[3]))
		return (0);
	spot = malloc(sizeof(t_spot));
	protect_malloc(scene, NULL, spot);
	spot->source = get_vec3(scene, *++tab);
	spot->ratio = ft_strtod(*++tab);
	scene->spot = spot;
	return (1);
}
