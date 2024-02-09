#include "miniRT.h"

int	is_in_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	is_posnum(const char *str)
{
	double	radius;

	if (!is_double(str))
		return (0);
	radius = ft_strtod(str);
	if (radius <= 0)
		return (0);
	return (1);
}

int	is_ratio(char *str)
{
	double	ratio;

	if (!is_double(str))
		return (0);
	ratio = ft_strtod(str);
	if (ratio < 0 || ratio > 1)
		return (0);
	return (1);
}

int	is_angle(char *str)
{
	double	angle;

	if (!is_double(str))
		return (0);
	angle = ft_strtod(str);
	if (!is_in_range(angle, 0, 180))
		return (0);
	return (1);
}
