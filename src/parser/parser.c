/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:39:57 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 17:35:29 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_line(t_scene *scene, char *line)
{
	int	ret;

	if (*line == 0 || line[0] == '\n' || ft_strlen(line) < 9)
		return (0);
	if (!ft_strncmp("A ", line, 2))
		ret = parse_ambient(scene, line + 2);
	else if (!ft_strncmp("C ", line, 2))
		ret = parse_camera(scene, line + 2);
	else if (!ft_strncmp("L ", line, 2))
		ret = parse_spot(scene, line + 2);
	else if (!ft_strncmp("sp ", line, 3))
		ret = parse_sphere(scene, line + 3);
	else if (!ft_strncmp("cy ", line, 3))
		ret = parse_cylinder(scene, line + 3);
	else if (!ft_strncmp("pl ", line, 3))
		ret = parse_plane(scene, line + 3);
	else
		return (0);
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
	int				fd;
	char			*line;

	if (!is_valid_filename(argv[1]))
		exit_minirt(scene,
			"Argument should be of the form:\n\t\t<filename>.rt", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_minirt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(scene, line))
		{
			close(fd);
			free(line);
			exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
