/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:50:01 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/14 17:33:36 by mwallage         ###   ########.fr       */
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

int     error_msg(const char *info)
{
	char    *errno_readable;

	write(STDERR_FILENO, "Error\n", ft_strlen("Error\n"));
	write(STDERR_FILENO, "miniRT: ", 8); 
	if (info)
		write(STDERR_FILENO, info, ft_strlen(info));
	errno_readable = strerror(errno);
	if (errno)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, errno_readable, ft_strlen(errno_readable));
	}
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

void	free_objects(t_object *head)
{
	t_object	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void	exit_minirt(t_scene *scene, char *message, int status)
{
	if (scene->objects)
		free_objects(scene->objects);
	if (status)
		error_msg(message);
	exit(status);
}

void	protect_malloc(void *check_ptr, t_scene *scene, void *free_ptr)
{
	if (check_ptr == NULL)
	{
		if (free_ptr)
			free(free_ptr);
		exit_minirt(scene, MALLOC_FAILED, MALLOC_EXITCODE);
	}
}
