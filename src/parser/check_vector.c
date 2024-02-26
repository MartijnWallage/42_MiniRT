/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:36 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/26 18:48:11 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_vector(t_build *build, char *str)
{
	char	**tab;

	if (ft_countchar(str, ',') != 2)
		return (0);
	tab = ft_split(str, ',');
	protect_malloc(build, tab);
	if (ft_tablen((void **)tab) != 3 || !is_real(tab[0]) || \
		!is_real(tab[1]) || !is_real(tab[2]))
	{
		ft_freetab((void **)tab);
		return (0);
	}
	ft_freetab((void **)tab);
	return (1);
}
