/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:04:02 by thofting          #+#    #+#             */
/*   Updated: 2024/02/26 18:53:50 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	write_ambient(int fd, t_minirt *minirt)
{
	write(fd, "A ", 2);
	ft_putreal(fd, minirt->scene->ambient.ratio);
	write(fd, " ", 1);
	ft_putcolor(fd, minirt->scene->ambient.color);
	write(fd, "\n", 1);
}

static void	write_camera(int fd, t_minirt *minirt)
{
	write(fd, "C ", 2);
	ft_putvector(fd, minirt->scene->camera.viewpoint);
	write(fd, " ", 1);
	ft_putvector(fd, minirt->scene->camera.direction);
	write(fd, " ", 1);
	ft_putnbr_fd(minirt->scene->camera.fov * 180 / M_PI, fd);
	write(fd, "\n", 1);
}

static void	write_spots(int fd, t_minirt *minirt)
{
	t_spotlight	*iter;

	iter = minirt->scene->spotlights;
	while (iter)
	{
		write(fd, "L ", 2);
		ft_putvector(fd, iter->source);
		write(fd, " ", 1);
		ft_putreal(fd, iter->diffuse);
		write(fd, " ", 1);
		ft_putcolor(fd, iter->color);
		write(fd, " ", 1);
		ft_putreal(fd, iter->specular);
		write(fd, "\n", 1);
		iter = iter->next;
	}
}

void	save_scene(t_minirt *minirt)
{
	int			fd;
	t_object	*iter;

	fd = open("scenes/output.rt", O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (fd < 0)
	{
		write(STDERR_FILENO, "Can't save scene\n", 17);
		return ;
	}
	write_ambient(fd, minirt);
	write_camera(fd, minirt);
	write_spots(fd, minirt);
	iter = minirt->scene->objects;
	while (iter)
	{
		write_object(fd, iter);
		iter = iter->next;
	}
	write(STDOUT_FILENO, "Scene saved in scenes/output.rt", 31);
	close(fd);
}
