/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/21 13:45:16 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	tablen(void **tab)
{
	int 	len;
	
	len = 0;
	while ((char *) tab[len])
		len++;
	return (len);
}

t_vec3	get_vec3(t_scene *scene, char *numbers)
{
	char	**tab;
	double	x;
	double	y;
	double	z;

	tab = ft_split(numbers, ',');
	if (!tab || tablen((void **)tab) != 3)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	x = ft_strtod(tab[0]);
	y = ft_strtod(tab[1]);
	z = ft_strtod(tab[2]);
	free_tab((void **)tab);
	return ((t_vec3){x, y, z});
}

int	get_color(t_scene *scene, char *rgb)
{
	char	**tab;
	int		color;

	tab = ft_split(rgb, ',');
	if (!tab || tablen((void **)tab) != 3)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	color = get_rgba(ft_atoi(tab[0]),
		ft_atoi(tab[1]),
		ft_atoi(tab[2]),
		0xff);
	free_tab((void **)tab);
	return (color);
}
