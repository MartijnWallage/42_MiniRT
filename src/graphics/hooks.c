/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:04:44 by mwallage          #+#    #+#             */
/*   Updated: 2024/01/18 14:04:51 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

void	ft_hook(void *param)
{
	t_mini_rt	*mini_rt;

	mini_rt = (t_mini_rt *)param;
	if (mlx_is_key_down(mini_rt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mini_rt->mlx);
}
