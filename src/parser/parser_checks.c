#include "miniRT.h"

int	is_numstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf("%s IS NOT\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_rbg(t_color color)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[0] < MIN_color || color[0] > MAX_color)
			return (0);
		i++;
	}
	return (1);
}

int	is_normal(double vector[3])
{
	if (sqrt(vector[0] * vector[0] + vector[1] * vector[1] \
		+ vector[2] * vector[2]) < EPSILON)
		return (1);
	return (0);
}

/* int is_vector(char *str)
{
	char	temp[MAX_LEN_DOUBLE + 1];
	int		pos_first;
	int		pos_second;

	pos_first = get_pos_nth_char(',', str, 1);
	pos_second = get_pos_nth_char(',', str, 1);
	if (!(pos_first > -1 && pos_first <  MAX_LEN_DOUBLE))
		return (-1);
	ft_strlcpy(temp, str, pos_first + 1);
	if (!is_valid_double(temp))
		return (-1);
	ft_strlcpy(temp, str + pos_first + 1, \
		pos_second - pos_first + 1);
	if (!is_valid_double(temp))
		return (-1);
	ft_strlcpy(temp, str + pos_second + 1, \
		ft_strlen(str) - pos_second + 1);
	if (!is_valid_double(temp))
		return (-1);
	return (1);
} */
