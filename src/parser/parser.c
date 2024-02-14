/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:57 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 14:00:17 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_line(t_scene *scene, char *line)
{
	char	**columns;
	int		ret;

	if (*line == 0 || line[0] == '\n')
		return (0);
	columns = ft_split(line, ' ');
	protect_malloc(scene, line, columns);
	if (!ft_strcmp("A", columns[0]) && !(scene->ambient))
		ret = parse_ambient(scene, columns);
	else if (!ft_strcmp("C", columns[0]) && !(scene->camera))
		ret = parse_camera(scene, columns);
	else if (!ft_strcmp("L", columns[0]) && !(scene->spot))
		ret = parse_spot(scene, columns);
	else if (!ft_strcmp("sp", columns[0]))
		ret = parse_sphere(scene, columns);
	else if (!ft_strcmp("cy", columns[0]))
		ret = parse_cylinder(scene, columns);
	else if (!ft_strcmp("pl", columns[0]))
		ret = parse_plane(scene, columns);
	else
		ret = 0;
	free_tab((void **)columns);
	return (ret);
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
	int		fd;
	char	*line;

	if (!is_valid_filename(argv[1]))
		exit_minirt(scene,
			"Argument should be of the form:\n\t\t<filename>.rt", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_minirt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(scene, line))
		{
			free(line);
			close(fd);
			exit_minirt(scene, PARSING_ERROR, EXIT_FAILURE);
		}		
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (scene->ambient == NULL || scene->camera == NULL)
		exit_minirt(scene, REQUIRE_LIGHT_AND_CAMERA, EXIT_FAILURE);
}
