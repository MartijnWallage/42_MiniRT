#include "miniRT.h"

void	free_objects_array(t_object **objects)
{
	int	i;

	i = 0;
	while (objects[i])
		free(objects[i++]);
	free(objects);
}

void	free_spots_array(t_light **spots)
{
	int	i;

	i = 0;
	while (spots[i])
		free(spots[i++]);
	free(spots);
}

void	exit_mini_rt(t_scene *scene, char *message, int status)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->objects)
		free_objects_array(scene->objects);
	if (scene->spots)
		free_spots_array(scene->spots);
	if (status == EXIT_FAILURE)
		printf("%s", message);
	exit(status);
}

static void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->objects = NULL;
	scene->spots = NULL;
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	init_scene(&scene);
	if (argc != 2)
		exit_mini_rt(&scene, ARGUMENT_ERROR, EXIT_FAILURE);
	parse_scene(argv, &scene);
	// print_scene(scene);
	exit_mini_rt(&scene, NULL, EXIT_SUCCESS);
	return (0);
}
