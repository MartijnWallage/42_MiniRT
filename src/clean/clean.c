/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:50:01 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/20 13:23:12 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	error_msg(const char *info)
{
	char	*errno_readable;

	write(STDERR_FILENO, "Error\n", 6);
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

void	free_spotlights(t_spotlight *head)
{
	t_spotlight	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void	exit_minirt(t_minirt *minirt, char *message, int status)
{
	if (minirt->scene->objects)
		free_objects(minirt->scene->objects);
	if (status)
		error_msg(message);
	exit(status);
}
