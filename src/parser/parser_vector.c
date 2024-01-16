/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:36 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:40:37 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_pos_nth_char(char c, char *str, int n)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (str[i] && cnt < n)
	{
		if (str[i] == c)
		{
			cnt++;
			if (cnt == n)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	is_normal(double vector[3])
{
	if (1 - sqrt(vector[0] * vector[0] + vector[1] * vector[1] \
		+ vector[2] * vector[2]) < EPSILON)
		return (1);
	return (0);
}

int is_vector(char *str)
{
	char	temp[MAX_LEN_DOUBLE + 1];
	int		pos_first;
	int		pos_second;

	pos_first = get_pos_nth_char(',', str, 1);
	pos_second = get_pos_nth_char(',', str, 2);
	if (!(pos_first > -1 && pos_first <  MAX_LEN_DOUBLE))
		return (0);
	ft_strlcpy(temp, str, pos_first + 1);
	if (!is_valid_double(temp))
		return (0);
	ft_strlcpy(temp, str + pos_first + 1, \
		pos_second - pos_first);
	if (!is_valid_double(temp))
		return (0);
	ft_strlcpy(temp, str + pos_second + 1, \
		ft_strlen(str) - pos_second - 1);
	if (!is_valid_double(temp))
		return (0);
	return (1);
}

int	is_rbg(double color[3])
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

void	str_to_vector(double dest[3], char *str)
{
	char	component[MAX_DIGITS_DOUBLE_INT_PART \
						+ MAX_DIGITS_DOUBLE_FRAC_PART + 2];
	int		pos;

	pos = 0;
	while (str[pos] != ',')
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[0] = ft_strtod(component);
	str += pos + 1;
	pos = 0;
	while (str[pos] != ',')
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[1] = ft_strtod(component);
	str += pos + 1;
	pos = 0;
	while (str[pos])
		pos++;
	ft_strlcpy(component, str, pos + 1);
	dest[2] = ft_strtod(component);
}
