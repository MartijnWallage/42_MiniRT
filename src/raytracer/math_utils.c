#include "miniRT.h"

/// @brief calculate the minimum of two values if positive
/// @param value1 first value
/// @param value2 second value
/// @return the minimal positive of the inputs, if both negative -1
double	ft_min_positive(double value1, double value2)
{
	if (value1 > value2 && value2 >= 0)
		return (value2);
	if (value1 >= 0)
		return (value1);
	return (-1);
}

/// @brief computes the square of the input parameter
/// @param value given number
/// @return square of the input
double	pow2(double value)
{
	return (value * value);
}

double	ft_abs(double value)
{
	if (value >= 0)
		return (value);
	return (-value);
}

double	norm2(t_vec3 vector)
{
	return (pow2(vector.x) + pow2(vector.y) + pow2(vector.z));
}