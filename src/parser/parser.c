/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:57 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 10:19:30 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	parse_line(t_build *build)
{
	if (build->line[0] == 0 || build->line[0] == '\n')
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	build->tab = ft_split(line, ' ');
	protect_malloc(build, build->tab);
	if (!ft_strcmp("A", build->tab[0]))
		parse_ambient(build);
	else if (!ft_strcmp("C", build->tab[0]))
		parse_camera(build);
	else if (!ft_strcmp("L", build->tab[0]))
		parse_spot(build);
	else if (!ft_strcmp("sp", build->tab[0]))
		parse_sphere(build);
	else if (!ft_strcmp("cy", build->tab[0]))
		parse_cylinder(build);
	else if (!ft_strcmp("pl", build->tab[0]))
		parse_plane(build);
	else
		exit_minirt(build, PARSING_ERROR, PARSING_EXITCODE);
	free_tab(build->tab);
}

int	is_valid_filename(char *path)
{
	int	len;

	len = ft_strlen(path);
	return (len > 3 && !ft_strcmp(path + len - 3, ".rt"));
}

/// @brief Parse the scene that is given as input into a struct
/// @param argv 	argv from main
/// @param scene 	end result
void	parse_scene(char **argv, t_scene *scene)
{
	t_build		build;

	if (!is_valid_filename(argv[1]))
		exit_minirt(scene, ARGUMENT_ERROR, EXIT_FAILURE);
	build.fd = open(argv[1], O_RDONLY);
	if (build.fd == -1)
		exit_minirt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	build.scene = scene;
	build.tab = NULL;
	build.line = get_next_line(fd);
	while (build.line)
	{
		parse_line(&build);
		free(line);
		build.line = get_next_line(build.fd);
	}
	close(build.fd);
}
