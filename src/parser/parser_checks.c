/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:51:49 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 15:07:38 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

int	is_posnum(t_build *build, const char *str)
{
	double	radius;

	if (!is_double(str))
		return (0);
	radius = ft_strtod(build, str);
	if (radius <= 0)
		return (0);
	return (1);
}

int	is_ratio(t_build *build, char *str)
{
	double	ratio;

	if (!is_double(str))
		return (0);
	ratio = ft_strtod(build, str);
	if (ratio < 0 || ratio > 1)
		return (0);
	return (1);
}

int	is_angle(t_build *build, char *str)
{
	double	angle;

	if (!is_double(str))
		return (0);
	angle = ft_strtod(build, str);
	if (!is_in_range(angle, 0, 180))
		return (0);
	return (1);
}

int	is_color(t_build *build, char *str)
{
	char	**tab;
	int		rgb[3];

	if (ft_countchar(str, ',') != 2)
		return (0);
	tab = ft_split(str, ',');
	protect_malloc(build, tab);
	if (tablen((void **)tab) != 3 || !is_double(tab[0]) || \
		!is_double(tab[1]) || !is_double(tab[2]))
	{
		free_tab((void **)tab);
		return (0);
	}
	rgb[0] = ft_atoi(tab[0]);
	rgb[1] = ft_atoi(tab[1]);
	rgb[2] = ft_atoi(tab[2]);
	if ((rgb[0] < 0 || rgb[0] > 255)
		|| (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
		return (0);
	free_tab((void **)tab);
	return (1);
}