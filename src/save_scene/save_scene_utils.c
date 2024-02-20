/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofting <thofting@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:12:43 by thofting          #+#    #+#             */
/*   Updated: 2024/02/20 21:12:45 by thofting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_putreal(int fd, t_real real)
{
	t_real	frac_part;
	int		i;

	ft_putnbr_fd((int)real, fd);
	if ((real - (int)real) < EPSILON)
		return ;
	write(fd, ".", 1);
	frac_part = real - (int)real;
	i = 0;
	while (i < 2)
	{
		frac_part *= 10;
		ft_putnbr_fd((int)frac_part, fd);
		frac_part = frac_part - (int)frac_part;
		i++;
	}
}

void	ft_putcolor(int fd, int color)
{
	ft_putnbr_fd(get_r(color), fd);
	write(fd, ",", 1);
	ft_putnbr_fd(get_g(color), fd);
	write(fd, ",", 1);
	ft_putnbr_fd(get_b(color), fd);
}

void	ft_putvector(int fd, t_vec3 vec)
{
	ft_putreal(fd, vec.x);
	write(fd, ",", 1);
	ft_putreal(fd, vec.y);
	write(fd, ",", 1);
	ft_putreal(fd, vec.z);
}
