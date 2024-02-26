/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_disk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:58:43 by thofting          #+#    #+#             */
/*   Updated: 2024/02/26 18:52:04 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_disk_tab(t_build *build)
{
	char		**tab;

	tab = build->tab;
	if (ft_tablen((void **)tab) != 7
		|| !is_vector(build, tab[1])
		|| !is_vector(build, tab[2])
		|| !is_posnum(build, tab[3])
		|| !is_color(build, tab[4])
		|| !is_ratio(build, build->tab[5])
		|| !is_posnum(build, build->tab[6]))
		exit_minirt_build(build, PARSING_ERROR, PARSING_EXITCODE);
}

void	parse_disk(t_build *build)
{
	t_object	*disk;
	char		**tab;
	t_scene		*scene;

	tab = build->tab;
	scene = build->scene;
	check_disk_tab(build);
	disk = malloc(sizeof(t_object));
	protect_malloc(build, disk);
	disk->type = DISK;
	disk->center = get_vec3(build, tab[1]);
	disk->direction = normalize(get_vec3(build, tab[2]));
	disk->radius = get_radius(build, tab[3]);
	disk->color = get_color(build, tab[4]);
	disk->up = compute_up_vector(build, disk->direction);
	disk->diffuse = 1.0;
	disk->shininess = 0.0;
	disk->diffuse = get_real(build, tab[5]);
	disk->shininess = get_real(build, tab[6]);
	disk->next = scene->objects;
	scene->objects = disk;
}
