/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 14:20:28 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	tablen(void **tab)
{
	int 	len;
	char	**chrtab;

	chrtab = (char **)tab;
	len = 0;
	while (chrtab[len])
		len++;
	return (len);
}

void	get_vector(t_scene *scene, t_vector vector, char *numbers)
{
	char	**tab;
	int		i;

	tab = ft_split(numbers, ',');
	if (!tab || tablen((void **)tab) != 3)
		exit_minirt(scene, PARSING_ERROR, PARSING_EXITCODE);
	i = -1;
	while (tab[++i])
		vector[i] = ft_strtod(tab[i]);
	free_tab((void **)tab);
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
