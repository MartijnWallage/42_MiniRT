#include "miniRT.h"

void	parse_ambient(t_scene *scene, char **tab)
{
	if (tablen((void **)tab) != 3 || !is_ratio(tab[1]) || \
		!is_color_vector(tab[2]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	scene->ambient = malloc(sizeof(t_ambient));
	protect_malloc(scene, NULL, scene->ambient);
	scene->ambient->ratio = ft_strtod(tab[1]);
	scene->ambient->color = get_color(scene, tab[2]);
}

void	parse_spot(t_scene *scene, char **tab)
{
	t_spot	*spot;

	if (tablen((void **)tab) != 4 || !is_vector(tab[1]) || \
		!is_ratio(tab[2]) || !is_color_vector(tab[3]))
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	spot = malloc(sizeof(t_spot));
	protect_malloc(scene, NULL, spot);
	spot->source = get_vec3(scene, *++tab);
	spot->ratio = ft_strtod(*++tab);
	spot->color = get_color(scene, *++tab);
	spot->next = scene->spots;
	scene->spots = spot;
}
