#include "miniRT.h"

void	calc_plane_intersection(t_ray *ray, t_object *plane, t_scene *scene)
{
	double		temp;
	double		factor;
	t_vector	temp_vec1;
	t_vector	temp_vec2;

	normalize(plane->normvect, temp_vec1);
	temp = dot(ray->normvect, temp_vec1);
	if (temp > -EPSILON && temp < EPSILON)
		return ;
	subtract(plane->center, scene->camera->viewpoint, temp_vec2);
	factor =  dot(temp_vec2, temp_vec1) / dot(ray->normvect, temp_vec1);
	if (factor <= 0)
		return ;
	if (ray->intersection < 0 || factor < ray->intersection)
	{
		ray->object = plane;
		ray->intersection = factor;
	}
}

// Calculations following https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection.html
void	calc_sphere_intersection(t_ray *ray, t_object *sphere, t_scene *scene)
{
	double		delta;
	double		b;
	double		c;
	double		temp;
	t_vector	temp_vec;

	subtract(scene->camera->viewpoint, sphere->center, temp_vec);
	b = 2 * dot(ray->normvect, temp_vec);
	temp = norm(temp_vec);
	c = pow2(temp) - sphere->radius * sphere->radius;
	delta = pow2(b) - 4 * c;
	if (delta < 0)
		return ;
	else if (delta < EPSILON)
		temp = -b / 2;
	else
	{
		delta = sqrt(delta);
		temp = ft_min_positive((-b + delta) / 2, (-b - delta) / 2);
	}
	if (temp > 0)
	{
		ray->intersection = temp;
		ray->object = sphere;
	}
}

void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder, t_scene *scene)
{
	ray = NULL;
	cylinder = NULL;
	scene = NULL;
	return ;
}
