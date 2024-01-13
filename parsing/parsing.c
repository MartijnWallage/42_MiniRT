#include "../miniRT.h"

static void parse_ambient(t_scene *scene, char **columns)
{
	if (get_str_array_len(columns) != 3 || scene->ambient)
	{
		free_str_array(columns);
		exit_mini_rt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	scene->ambient = malloc(sizeof(t_light));
	if (!scene->ambient)
	{
		free_str_array(columns);
		exit_mini_rt(scene, MALLOC_FAILED, EXIT_FAILURE);
	}
}

static void	parse_line(t_scene *scene, char *line)
{
	char	**columns;

	scene = NULL;
	line = NULL;
	columns = ft_split(line, ' ');
	free(line);
	if (columns == NULL)
		exit_mini_rt(scene, MALLOC_FAILED, EXIT_FAILURE);
	if (ft_strcmp("A", columns[0]))
		parse_ambient(scene, columns);
	/*
	else if (ft_strcmp("C", columns[0]))
		parse_camera(scene, columns);
	else if (ft_strcmp("L", columns[0]))
		parse_light(scene, columns);
	else if (ft_strcmp("sp", columns[0]))
		parse_sphere(scene, columns);
	*/
	else
	{
		free_str_array(columns);
		exit_mini_rt(scene, PARSING_ERROR, EXIT_FAILURE);
	}
	free_str_array(columns);
}

void	parse_scene(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_mini_rt(scene, CANNOT_OPEN_FILE, EXIT_FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		parse_line(scene, line);
	}
	if (scene->ambient == NULL || scene->camera == NULL)
		exit_mini_rt(scene, REQUIRE_LIGHT_AND_CAMERA, EXIT_FAILURE);
}
