#include "miniRT.h"

void	parse_camera(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_normal_vector(tab[2]) || !is_angle(tab[3]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	scene->camera = malloc(sizeof(t_camera));
	protect_malloc(scene, NULL, scene->camera);
	scene->camera->viewpoint = get_vec3(scene, tab[1]);
	scene->camera->direction = normalize(get_vec3(scene, tab[2]));
	scene->camera->fov = ft_strtod(tab[3]);
}
