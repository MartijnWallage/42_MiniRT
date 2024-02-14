/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:14 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 17:38:32 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	extract_int(const char *source, char *dest)
{
	int	i;

	i = 0;
	while (source[i] && is_digit(source[i]) && i <= MAX_DIGITS_INT_PART)
	{
		dest[i] = source[i];
		i++;
	}
	if (i == MAX_DIGITS_INT_PART + 1)
		dest[0] = 'e';
	else
		dest[i] = '\0';
	return ;
}

static void	extract_frac(const char *source, char *dest)
{
	int	i;
	int	j;

	i = 0;
	while (source[i] && is_digit(source[i]))
		i++;
	if (!source[i])
		dest[0] = '\0';
	i++;
	j = 0;
	while (source[i] && j <= MAX_DIGITS_FRAC_PART)
		dest[j++] = source[i++];
	dest[j] = '\0';
	if (j == MAX_DIGITS_INT_PART + 1)
		dest[0] = 'e';
	else
		dest[j] = '\0';
	return ;
}

static int	is_numstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

// checks if a given string can be converted to a double. Not all
// double convertable strings are considered valid, there are limitations!
int	is_double(const char *str)
{
	char	**tab;
	int		return_value;

	if (str == NULL || str[0] == '\n' || str[0] == '\0')
		return (0);
	if (str[0] == '-')
		str++;
	if (str[0] == '.' || ft_countchar(str, '.') > 1)
		return (0);
	tab = ft_split(str, '.');
	if (!tab)
		return (0);
	return_value = is_numstr(tab[0]) && \
		(ft_strlen(tab[0]) <= MAX_DIGITS_INT_PART);
	if (tablen((void **)tab) == 2)
		return_value = return_value && is_numstr(tab[1]) && \
			(ft_strlen(tab[1]) <= MAX_DIGITS_FRAC_PART);
	free_tab((void **)tab);
	return (return_value);
}

double	ft_strtod(const char *str)
{
	char	int_part[MAX_DIGITS_INT_PART + 2];
	char	frac_part[MAX_DIGITS_FRAC_PART + 1];
	double	result;
	double	frac;
	int		i;

	extract_int(str, (char *)int_part);
	extract_frac(str, (char *)frac_part);
	result = (double)ft_atoi(int_part);
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
