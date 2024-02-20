/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_real.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:14 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 16:11:37 by mwallage         ###   ########.fr       */
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

static char	**make_tab(t_build *build, const char *str)
{
	char	**tab;

	tab = ft_split(str, '.');
	protect_malloc(build, tab);
	if (ft_tablen((void **)tab) == 0 || ft_tablen((void **)tab) > 2)
	{
		ft_freetab((void **)tab);
		exit_minirt_build(build, "invalid t_real", PARSING_EXITCODE);
	}
	return (tab);
}

t_real	get_real(t_build *build, const char *str)
{
	t_real	result;
	int		div;
	char	**tab;
	char	*frac_str;

	if (!str || str[0] == 0 || (!ft_isdigit(str[0]) && str[0] != '-'))
		exit_minirt_build(build, "invalid t_real", PARSING_EXITCODE);
	tab = make_tab(build, str);
	result = (t_real)ft_atoi(tab[0]);
	if (tab[1] == NULL)
		return (result);
	div = 10;
	frac_str = tab[1];
	while (ft_isdigit(*frac_str))
	{
		result += (t_real)(*tab[1] - '0') / div;
		div *= 10;
		frac_str++;
	}
	ft_freetab((void **)tab);
	return (result);
}
