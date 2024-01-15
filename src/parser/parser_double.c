/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:14 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 14:40:17 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// if the char given as argument is not contained in str, 
// return len of str, if it is contained once, return position in string,
// if contained more than once, return a negative value.
static int  get_unique_char_pos(char c, const char *str)
{
	int cnt;
	int pos;
	int i;

	cnt = 0;
	i = 0;
	pos = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == c)
		{
			pos = i;
			cnt++;
		}
		i++;
		if (cnt > 1)
			return (-1);
	}
	return (pos);
}

// checks if a given string can be converted to a double. Not all
// double convertable strings are considered valid, there are limitations!
int	is_valid_double(const char *str)
{
	int		pos_point;
	char	int_part[MAX_DIGITS_DOUBLE_INT_PART + 1];
	char	frac_part[MAX_DIGITS_DOUBLE_FRAC_PART + 1];

	if (str == NULL)
		return (0);
	if (str[0] == '-')
		str++;
	pos_point = get_unique_char_pos('.', str);
	if (pos_point < 0)
		return (0);
	if (pos_point > MAX_DIGITS_DOUBLE_INT_PART || (int)ft_strlen(str) \
		- pos_point > MAX_DIGITS_DOUBLE_FRAC_PART + 1)
			return (0);
	ft_strlcpy(int_part, str, pos_point + 1);
	if (!is_numstr(int_part))
		return (0);
	if (pos_point == (int)ft_strlen(str))
		return (1);
	ft_strlcpy(frac_part, str + pos_point + 1, ft_strlen(str) + 1);
	if (!is_numstr(frac_part))
		return (0);
	return (1);
}

// converts a valid string ito a double value, restrictions are 
double	ft_strtod(char *str)
{
	char	int_part[MAX_DIGITS_DOUBLE_INT_PART + 1];
	char	frac_part[MAX_DIGITS_DOUBLE_FRAC_PART + 1];
	double	result;
	int		pos_point;
	double	frac;
	int		i;

	pos_point = get_unique_char_pos('.', str);
	ft_strlcpy(int_part, str, pos_point + 1);
	result = (double)ft_atoi(int_part);
	if (pos_point == (int)ft_strlen(str))
		return (result);
	ft_strlcpy(frac_part, str + pos_point + 1, ft_strlen(str) + 1);
	frac = (double)ft_atoi(frac_part);
	i = (int)ft_strlen(frac_part);
	while (i > 0)
	{
		frac /= 10;
		i--;
	}
	result += frac;
	return (result);
}
