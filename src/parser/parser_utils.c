/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:40:26 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/17 19:26:54 by mwallage         ###   ########.fr       */
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

void	get_vector(t_vector vector, char *numbers)
{
	char	**tab;
	int		i;

	tab = ft_split(numbers, ',');
	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		vector[i] = ft_strtod(tab[i]);
	free_tab((void **)tab);
}

void	get_color(t_color color, char *rgb)
{
	char	**tab;
	int		i;

	tab = ft_split(rgb, ',');
	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		color[i] = (unsigned char)ft_atoi(tab[i]);
	free_tab((void **)tab);
}