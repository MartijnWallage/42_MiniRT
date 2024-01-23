#include "miniRT.h"

// source https://en.wikipedia.org/wiki/Rotation_matrix#Basic_3D_rotations
t_vec3	rotate_x_axis(t_vec3 vector, double alpha)
{
	double	cos_alpha;
	double	sin_alpha;
	t_vec3	result;

	cos_alpha = cos(alpha);
	sin_alpha = sin(alpha);
	result.x = vector.x;
	result.y = vector.y * cos_alpha - vector.z * sin_alpha;
	result.z = vector.y * sin_alpha + vector.z * cos_alpha;
	return (result);
}

t_vec3	rotate_y_axis(t_vec3 vector, double alpha)
{
	double	cos_alpha;
	double	sin_alpha;
	t_vec3	result;

	cos_alpha = cos(alpha);
	sin_alpha = sin(alpha);
	result.x = vector.x * cos_alpha + vector.z * sin_alpha;
	result.y = vector.y;
	result.z = -vector.x * sin_alpha + vector.z * cos_alpha;
	return (result);
}

t_vec3	rotate_z_axis(t_vec3 vector, double alpha)
{
	double	cos_alpha;
	double	sin_alpha;
	t_vec3	result;

	cos_alpha = cos(alpha);
	sin_alpha = sin(alpha);
	result.x = vector.x * cos_alpha - vector.y * sin_alpha;
	result.y = vector.x * sin_alpha + vector.y * cos_alpha;
	result.z = vector.z;
	return (result);
}