#include "miniRT.h"

typedef	enum	e_int_type
{
	BOTH_NEGATIVE,
	FIRST_VALUE,
	SECOND_VALUE,
} t_int_type;

typedef struct s_intersections
{
	t_vec3	n_x_a;
	double	norm_nxa;
	t_vec3	b_x_a;
	t_vec3	b;
	double	d_hull;
	double	d_cap;
	double	t_hull;
	int		orientation_cap;
} t_intersections;

double	norm2(t_vec3 vector)
{
	return (pow2(vector.x) + pow2(vector.y) + pow2(vector.z));
}

static t_intersections	init_ints_struct(t_ray	*ray, t_object *cylinder)
{
	t_intersections	ints;

	ints.n_x_a = cross(ray->direction, cylinder->direction);
	ints.b = subtract(cylinder->center, ray->origin);
	ints.b_x_a = cross(ints.b, cylinder->direction);
	ints.d_cap = -1;
	ints.d_hull = -1;
	return (ints);
}

t_int_type	get_min_positive(double	value1, double value2)
{
	if (value1 < 0 && value2 < 0)
		return (BOTH_NEGATIVE);
	else if (value1 < 0 && value2 > 0)
		return (SECOND_VALUE);
	else if (value2 < 0 && value1 > 0)
		return (FIRST_VALUE);
	else if (value1 <= value2)
		return (FIRST_VALUE);
	else if (value2 < value1)
		return (SECOND_VALUE);
	return (BOTH_NEGATIVE);
}

void	calc_cylinder_hull_intersections(t_intersections *ints, \
	t_ray *ray, t_object *cylinder)
{
	t_vec3		temp;
	double		norm_nxa2;
	double		dot_temp;
	double		delta;
	double		d1;
	double		d2;
	double		t1;
	double		t2;
	t_int_type	type;

	norm_nxa2 = norm2(ints->n_x_a);
	if (norm_nxa2 < EPSILON)
		return ;
	delta = norm_nxa2 * pow2(cylinder->radius) - \
		pow2(dot(ints->b, ints->n_x_a));
	if (delta < 0)
		return ;
	dot_temp = dot(ints->n_x_a, ints->b_x_a);
	d1 = (dot_temp + sqrt(delta)) / norm_nxa2;
	d2 = (dot_temp - sqrt(delta)) / norm_nxa2;
	t1 = 0;
	t2 = 0;
	if (d1 > 0)
	{
		temp = subtract(multiply(ray->direction, d1), ints->b);
		t1 = dot(cylinder->direction, temp);
		if (t1 < - cylinder->height / 2 || t1 > cylinder->height / 2)
			d1 = -1;
	}
	if (d2 > 0)
	{
		temp = subtract(multiply(ray->direction, d2), ints->b);
		t2 = dot(cylinder->direction, temp);
		if (t2 < -cylinder->height / 2 || t2 > cylinder->height / 2)
			d2 = -1;
	}
	type = get_min_positive(d1, d2);
	if (type == FIRST_VALUE)
	{
		ints->t_hull = t1;
		ints->d_hull = d1;
	}
	else if (type == SECOND_VALUE)
	{
		ints->t_hull = t2;
		ints->d_hull = d2;
	}
	return ;
}

void calc_cylinder_cap_intersections(t_intersections *ints, t_ray *ray, t_object *cylinder)
{
	double		dot_temp;
	t_vec3		cap_center;
	double		d1;
	double		d2;
	t_int_type	type;
	t_vec3		half_axis;

	dot_temp = dot(ray->direction, cylinder->direction);
	if (ft_abs(dot_temp) < EPSILON)
	{
		ints->d_cap = -1;
		return ;
	}
	half_axis = multiply(cylinder->direction, cylinder->height / 2);
	cap_center = subtract(add(cylinder->center, half_axis), ray->origin);
	d1 = dot(cylinder->direction, cap_center) / dot_temp;
	if (norm2(subtract(multiply(ray->direction, d1), cap_center)) >= pow2(cylinder->radius))
		d1 = -1;
	cap_center = subtract(subtract(cylinder->center, half_axis), ray->origin);
	d2 = dot(cylinder->direction, cap_center) / dot_temp;
	if (norm2(subtract(multiply(ray->direction, d2), cap_center)) >= pow2(cylinder->radius))
		d2 = -1;
	type = get_min_positive(d1, d2);
	if (type == SECOND_VALUE)
	{
		ints->orientation_cap = -1;
		ints->d_cap = d2;
	}
	else if (type == FIRST_VALUE)
	{
		ints->orientation_cap = 1;
		ints->d_cap = d1;
	}
}

void	calc_cylinder_intersection(t_ray *ray, t_object *cylinder)
{
	t_intersections	ints;
	t_vec3			normal_surface;
	double			t;
	t_int_type		type;

	t = 0;
	ints = init_ints_struct(ray, cylinder);
	calc_cylinder_hull_intersections(&ints, ray, cylinder);
	calc_cylinder_cap_intersections(&ints, ray, cylinder);
	type = get_min_positive(ints.d_hull, ints.d_cap);
	if (type == FIRST_VALUE)
	{
		ray->object = cylinder;
		ray->intersection = ints.d_hull;
		normal_surface = multiply(ray->direction, ray->intersection);
		normal_surface = subtract(normal_surface, ints.b);
		ray->normal = normalize(subtract(normal_surface, multiply(cylinder->direction, ints.t_hull)));
	}
	if (type == SECOND_VALUE)
	{
		ray->object = cylinder;
		ray->intersection = ints.d_cap;
		ray->normal = multiply(cylinder->direction, ints.orientation_cap);
	}
}