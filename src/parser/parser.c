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
	str_to_vector(scene->ambient->colour, columns[2]);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0 ||
		!is_rbg(scene->ambient->colour))
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	printf("VALUES %f, %f,%f,%f\n", scene->ambient->ratio, scene->ambient->colour[0], \
				scene->ambient->colour[1],scene->ambient->colour[2]);
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
		exit_minirt(scene, MALLOC_FAILED, EXIT_FAILURE);
	}
	str_to_vector(scene->camera->viewpoint, columns[1]);
	str_to_vector(scene->camera->normvect, columns[2]);
	scene->camera->fov = ft_strtod(columns[3]);
	if (!is_normal(scene->camera->normvect) || scene->camera->fov < 0.0 ||
		scene->camera->fov > 180.0)
	{
		free_tab((void **) columns);
		exit_minirt(scene, MALLOC_FAILED, EXIT_FAILURE);
	}
}

static void	parse_line(t_scene *scene, char *line)
{
	char	**columns;

	columns = ft_split(line, ' ');
	free(line);
	printf("COLUMNS %s, %s, %s\n", columns[0], columns[1], columns[2]);
	if (columns == NULL)
		exit_minirt(scene, MALLOC_FAILED, EXIT_FAILURE);
	if (!ft_strcmp("A", columns[0]))
	{
		printf("PARSE AMBIENT\n");
		parse_ambient(scene, columns);
	}
	else if (!ft_strcmp("C", columns[0]))
	{
		printf("PARSE CAMERA\n");
		parse_camera(scene, columns);
	}
	/*
	else if (!ft_strcmp("L", columns[0]))
		parse_light(scene, columns);
	else if (!ft_strcmp("sp", columns[0]))
		parse_sphere(scene, columns);
	*/
	else
	{
		free_tab((void **)columns);
		exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	free_tab((void **)columns);
}

void	parse_scene(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;
	int		idx_extension;

	idx_extension = (int)ft_strlen(argv[1]) - 3;
	if (idx_extension < 0 || ft_strcmp(argv[1] + idx_extension,".rt"))
		exit_minirt(scene, "FAIL", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_minirt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!ft_strcmp(line,""))
			continue;
		parse_line(scene, line);
	}
	if (scene->ambient == NULL || scene->camera == NULL)
		exit_minirt(scene, REQUIRE_LIGHT_AND_CAMERA, EXIT_FAILURE);
}
