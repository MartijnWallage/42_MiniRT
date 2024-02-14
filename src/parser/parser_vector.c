/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:36 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 16:20:26 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_normal_vector(char *str)
{
	char	**tab;

	if (!is_vector(str))
		return (0);
	if (!CHECK_PARSING_NORMAL)
		return (1);
	tab = ft_split(str, ',');
	if (!tab)
		return (0);
	if (ft_abs(pow2(ft_strtod(tab[0])) + pow2(ft_strtod(tab[1])) \
		+ pow2(ft_strtod(tab[2])) - 1) > EPSILON)
	{
		free_tab((void **)tab);
		return (0);
	}
	free_tab((void **)tab);
	return (1);
}

int	is_vector(char *str)
{
	char	**tab;

	if (ft_countchar(str, ',') != 2)
		return (0);
	tab = ft_split(str, ',');
	if (!tab)
		return (0);
	if (tablen((void **)tab) != 3 || !is_double(tab[0]) || \
		!is_double(tab[1]) || !is_double(tab[2]))
	{
		free_tab((void **)tab);
		return (0);
	}
	free_tab((void **)tab);
	return (1);
}
