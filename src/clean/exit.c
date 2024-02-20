/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:17:24 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 13:17:39 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	exit_minirt_build(t_build *build, char *message, int status)
{
	if (build->tab)
		ft_freetab((void **)build->tab);
	if (build->line)
		free(build->line);
	if (build->fd)
		close(build->fd);
	if (build->scene->objects)
		free_objects(build->scene->objects);
	if (build->scene->spotlights)
		free_spotlights(build->scene->spotlights);
	if (status)
		error_msg(message);
	exit(status);
}

void	protect_malloc(t_build *build, void *check_ptr)
{
	if (check_ptr == NULL)
		exit_minirt_build(build, MALLOC_FAILED, MALLOC_EXITCODE);
}
