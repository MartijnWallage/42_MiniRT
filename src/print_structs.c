#include "miniRT.h"

void	print_scene(t_scene *scene)
{
	int	i;

	printf("\n****************************\n");
	printf("AMBIENT LIGHT:\n");
	printf("Ratio: %lf\n", scene->ambient->ratio);
	printf("color: %lf, %lf, %lf\n",
		scene->ambient->color[0],
		scene->ambient->color[1], 
		scene->ambient->color[2]);
	printf("Source: %lf, %lf, %lf\n",
		scene->ambient->source[0],
		scene->ambient->source[1],
		scene->ambient->source[2]);
	printf("\nSPOT LIGHTS:\n");
	i = -1;
	while (scene->spots && scene->spots[++i])
	{
		printf("Ratio: %lf\n", scene->spots[i]->ratio);
		printf("color: %lf, %lf, %lf\n",
			scene->spots[i]->color[0],
			scene->spots[i]->color[1], 
			scene->spots[i]->color[2]);
		printf("Source: %lf, %lf, %lf\n",
			scene->spots[i]->source[0],
			scene->spots[i]->source[1],
			scene->spots[i]->source[2]);
	}
	printf("CAMERA:\n");
	printf("Fov: \t\t%d\n", scene->camera->fov);
	printf("Viewpoint: %lf, %lf, %lf\n",
		scene->camera->viewpoint[0],
		scene->camera->viewpoint[1], 
		scene->camera->viewpoint[2]);
	printf("Norm vector: %lf, %lf, %lf\n",
		scene->camera->normvect[0],
		scene->camera->normvect[1],
		scene->camera->normvect[2]);
	printf("OBJECTS:\n");
	i = -1;
	while (scene->objects && scene->objects[++i])
	{
		printf("Type: %d\n", scene->objects[i]->type);
		printf("Center: %lf, %lf, %lf\n",
			scene->objects[i]->center[0],
			scene->objects[i]->center[1],
			scene->objects[i]->center[2]);
		printf("Color: %x, %x, %x\n",
			scene->objects[i]->color[0],
			scene->objects[i]->color[1],
			scene->objects[i]->color[2]);
		printf("Norm vector: %lf, %lf, %lf\n",
			scene->objects[i]->normvect[0],
			scene->objects[i]->normvect[1],
			scene->objects[i]->normvect[2]);
		printf("Diameter: %lf\n",
			scene->objects[i]->diameter);
		printf("Height: %lf\n",
			scene->objects[i]->height);
	}
	printf("*****************************\n");
}