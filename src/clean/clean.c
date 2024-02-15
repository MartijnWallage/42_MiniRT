/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:50:01 by mwallage          #+#    #+#             */
/*   Updated: 2024/02/15 10:13:48 by mwallage         ###   ########.fr       */
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

void	exit_minirt(t_build *build, char *message, int status)
{
	if (build->tab)
		free_tab(build->tab);
	if (build->str)
		free(build->str);
	if (build->fd)
		close(fd);
	if (build->scene->objects)
		free_objects(build->scene->objects);
	if (status)
		error_msg(message);
	exit(status);
}

void	protect_malloc(t_build *build, void *check_ptr)
{
	if (check_ptr == NULL)
		exit_minirt(build, MALLOC_FAILED, MALLOC_EXITCODE);
}
