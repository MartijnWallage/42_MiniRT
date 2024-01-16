/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:50:01 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/15 15:50:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_tab(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}


void	exit_minirt(t_scene *scene, char *message, int status)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->objects)
		free_tab((void **) scene->objects);
	if (scene->spots)
		free_tab((void **) scene->spots);
	if (status == EXIT_FAILURE)
		printf("%s", message);
	exit(status);
}

void	protect_malloc(t_scene *scene, void *free_ptr, void *check_ptr)
{
	if (check_ptr == NULL)
	{
		if (free_ptr)
			free(free_ptr);
		exit_minirt(scene, MALLOC_FAILED, 1);
	}
}
