/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofting <thofting@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:15:56 by thofting          #+#    #+#             */
/*   Updated: 2024/02/20 21:15:57 by thofting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	write_direction(int fd, t_object *object)
{
	write(fd, " ", 1);
	ft_putvector(fd, object->direction);
}

static void	write_radius(int fd, t_object *object)
{
	ft_putreal(fd, object->radius * 2);
	write(fd, " ", 1);
}

static void	write_bonus(int fd, t_object *object)
{
	write(fd, " ", 1);
	ft_putreal(fd, object->diffuse);
	write(fd, " ", 1);
	ft_putreal(fd, object->shininess);
}

void	write_object(int fd, t_object *object)
{
	if (object->type == SPHERE)
		write(fd, "sp ", 3);
	else if (object->type == PLANE)
		write(fd, "pl ", 3);
	else if (object->type == CYLINDER)
		write(fd, "cy ", 3);
	else if (object->type == DISK)
		write(fd, "di ", 3);
	ft_putvector(fd, object->center);
	if (object->type != SPHERE)
		write_direction(fd, object);
	write(fd, " ", 1);
	if (object->type != PLANE)
		write_radius(fd, object);
	if (object->type == CYLINDER)
	{
		ft_putreal(fd, object->height);
		write(fd, " ", 1);
	}
	ft_putcolor(fd, object->color);
	if (BONUS)
		write_bonus(fd, object);
	write(fd, "\n", 1);
}
