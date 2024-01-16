# include "miniRT.h"

void	ft_hook(void *param)
{
	t_mini_rt	*mini_rt;

	mini_rt = (t_mini_rt *)param;
	if (mlx_is_key_down(mini_rt->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mini_rt->mlx);
}