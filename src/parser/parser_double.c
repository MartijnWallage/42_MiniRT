/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:14 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 15:13:59 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

double	ft_strtod(t_build *build, const char *str)
{
	double	result;
	double	frac;
	int		i;
	char	**tab;
	
	if (!str || str[0] == 0 || str[0] == '.')
		exit_minirt_build(build, "invalid double", PARSING_EXITCODE);
	tab = ft_split(str, '.');
	protect_malloc(build, tab);
	if (tablen((void**)tab) == 0 || tablen((void**)tab) > 2)
		exit_minirt_build(build, "invalid double", PARSING_EXITCODE);
	result = (double)ft_atoi(tab[0]);
	if (tab[1] == NULL)
		return (result);
	frac = (double)ft_atoi(tab[1]);
	i = (int)ft_strlen(tab[1]);
	while (i > 0)
	{
		frac /= 10;
		i--;
	}
	result += frac;
	return (result);
}
