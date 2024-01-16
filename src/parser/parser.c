/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:57 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:40:02 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void parse_ambient(t_scene *scene, char **columns)
{
	if (get_str_array_len(columns) != 3 || scene->ambient)
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	scene->ambient = malloc(sizeof(t_light));
	if (!scene->ambient || !is_valid_double(columns[1]) || \
		!is_vector(columns[2]))
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	scene->ambient->ratio = ft_strtod(columns[1]);
	str_to_vector(scene->ambient->color, columns[2]);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0 ||
		!is_rbg(scene->ambient->color))
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	printf("VALUES %f, %f,%f,%f\n", scene->ambient->ratio, scene->ambient->color[0], \
				scene->ambient->color[1],scene->ambient->color[2]);
}

void parse_camera(t_scene *scene, char **columns)
{
	if (get_str_array_len(columns) != 4 || scene->camera)
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera || !is_vector(columns[1]) || \
		!is_vector(columns[2]) || !is_valid_double(columns[3]))
	{
		free_tab((void **) columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	str_to_vector(scene->camera->viewpoint, columns[1]);
	str_to_vector(scene->camera->normvect, columns[2]);
	scene->camera->fov = ft_strtod(columns[3]);
	if (!is_normal(scene->camera->normvect) || scene->camera->fov < 0.0 ||
		scene->camera->fov > 180.0)
	{
		free_tab((void **) columns);
		exit_minirt(scene, "not a valid vector", EXIT_FAILURE);
	}
}

static void	parse_line(t_scene *scene, char *line)
{
	char	**columns;

	if (*line == 0)
		return ;
	columns = ft_split(line, ' ');
	free(line);
	if (columns == NULL)
		exit_minirt(scene, MALLOC_FAILED, EXIT_FAILURE);
	if (!ft_strcmp("A", columns[0]))
		parse_ambient(scene, columns);
	else if (!ft_strcmp("C", columns[0]))
		parse_camera(scene, columns);
	else if (!ft_strcmp("L", columns[0]))
		parse_light(scene, columns);
	else if (!ft_strcmp("sp", columns[0]))
		parse_sphere(scene, columns);
	else if (!ft_strcmp("cy", columns[0]))
		parse_cylinder(scene, columns);
	else if (!ft_strcmp("pl", columns[0]))
		parse_plane(scene, columns);
	else
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	free_tab((void **)columns);
}

int	is_valid_arg(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	return (len > 3 && arg[len - 4] != '/' && !ft_strcmp(arg + len - 3, ".rt"));
}

/// @brief Parse the scene that is given as input into a struct
/// @param argv 	argv from main
/// @param scene 	end result
void	parse_scene(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!is_valid_arg(argv[1]))
		exit_minirt(scene,
			"Argument should be of the form:\n\t\t<filename>.rt\n", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_minirt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(scene, line);
		line = get_next_line(fd);
	}
	if (scene->ambient == NULL || scene->camera == NULL)
		exit_minirt(scene, REQUIRE_LIGHT_AND_CAMERA, EXIT_FAILURE);
}
