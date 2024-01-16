#include "miniRT.h"
/*
void mlx_draw_pixel(unsigned char *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

//= Public =//

void    ft_mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	MLX_NONNULL(image);
	MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}
*/
void	put_circle(mlx_image_t* image)
{
	unsigned int	x;
	unsigned int	y;
	unsigned char	*pxl;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			if (((double)x - 100)*((double)x - 100) + ((double)y - 100)*((double)y - 100) > 250 && \
				((double)x - 100)*((double)x - 100) + ((double)y - 100)*((double)y - 100) < 270)
			{
				pxl = &image->pixels[(y * image->width + x) * sizeof(int)];
				*(pxl++) = 0;
				*(pxl++) = 0;
				*(pxl++) = 0;
				*(pxl++) = 0;
			}
			x++;
		}
		y++;
	}
}