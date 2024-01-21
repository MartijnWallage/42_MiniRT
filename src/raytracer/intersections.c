#include "miniRT.h"

void	calc_plane_intersection(t_ray *ray, t_object *plane, t_scene *scene)
{
	double		temp;
	double		factor;
	t_vec3	temp_vec1;
	t_vec3	temp_vec2;

	temp_vec1 = normalize(plane->normvect);
	temp = dot(ray->normvect, temp_vec1);
	if (temp > -EPSILON && temp < EPSILON)
		return ;
	temp_vec2 = subtract(plane->center, scene->camera->viewpoint);
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
	t_vec3	temp_vec;

	temp_vec = subtract(scene->camera->viewpoint, sphere->center);
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

// Calculations following https://en.wikipedia.org/wiki/Line-cylinder_intersection
void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder, t_scene *scene)
{
	t_vec3	n_x_a;
	t_vec3	b_x_a;
	t_vec3	b;
	t_vec3	temp1;
	t_vec3	temp2;
	double		norm_temp;
	double		dot_temp;
	double		delta;
	double		t1;
	double		t2;
	double		d1;
	double		d2;
	double		d_final;

	n_x_a = cross(ray->normvect, cylinder->normvect);
	b = subtract(cylinder->center, scene->camera->viewpoint);
	norm_temp = norm(n_x_a);
	if (norm_temp < EPSILON)
		return ;
	delta = dot(n_x_a, n_x_a) * pow2(cylinder->radius) - \
		pow2(dot(b, n_x_a));
	if (delta < 0)
		return ;
	b_x_a = cross(b, cylinder->normvect);
	dot_temp = dot(n_x_a, b_x_a);
	d1 = (dot_temp + sqrt(delta)) / norm_temp;
	temp1 = multiply(ray->normvect, d1);
	temp2 = subtract(temp1, b);
	t1 = dot(cylinder->normvect, temp2);
	d2 = (dot_temp - sqrt(delta)) / norm_temp;
	temp1 = multiply(ray->normvect, d2);
	temp2 = subtract(temp1, b);
	t2 = dot(cylinder->normvect, temp2);
	if (t1 < - cylinder->height / 2 || t1 > cylinder->height / 2 )
		d1 = -1;
	if (t2 < - cylinder->height / 2 || t2 > cylinder->height / 2 )
		d2 = -1;
	d_final = ft_min_positive(d1, d2);
	if (d_final >= 0 && (ray->intersection < 0 || d_final < ray->intersection))
	{
		ray->object = cylinder;
		ray->intersection = d_final;
	}
	return ;
}
