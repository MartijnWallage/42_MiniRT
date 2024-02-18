/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:14 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/18 12:48:16 by mwallage         ###   ########.fr       */
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

// checks if a given string can be converted to a t_real. Not all
// t_real convertable strings are considered valid, there are limitations!
int	is_real(const char *str)
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
	if (ft_tablen((void **)tab) == 2)
		return_value = return_value && is_numstr(tab[1]) && \
			(ft_strlen(tab[1]) <= MAX_DIGITS_FRAC_PART);
	ft_freetab((void **)tab);
	return (return_value);
}

t_real	get_real(t_build *build, const char *str)
{
	t_real	result;
	t_real	frac;
	int		i;
	char	**tab;

	if (!str || str[0] == 0 || str[0] == '.')
		exit_minirt_build(build, "invalid t_real", PARSING_EXITCODE);
	tab = ft_split(str, '.');
	protect_malloc(build, tab);
	if (ft_tablen((void **)tab) == 0 || ft_tablen((void **)tab) > 2)
		exit_minirt_build(build, "invalid t_real", PARSING_EXITCODE);
	result = (t_real)ft_atoi(tab[0]);
	if (tab[1] == NULL)
		return (result);
	frac = (t_real)ft_atoi(tab[1]);
	i = (int)ft_strlen(tab[1]);
	while (i > 0)
	{
		frac /= 10;
		i--;
	}
	result += frac;
	return (result);
}
