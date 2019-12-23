/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/23 18:52:51 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel(t_data *my_mlx, int x, int y, int color)
{
	int pos;

	if (x >= 0 && x < 1280 && y >= 0 && y < 720)
	{
		pos = y * my_mlx->line_length + x * (my_mlx->bpp / 8);
		*(my_mlx->addr + pos + 0) = (char)((color & 0x00FFFFFF) >> 0);
		*(my_mlx->addr + pos + 1) = (char)((color & 0x0000FF00) >> 8);
		*(my_mlx->addr + pos + 2) = (char)((color & 0x00FF0000) >> 16);
	}
}

t_data	*init_my_mlx(void)
{
	t_data	*my_mlx;

	my_mlx = malloc(sizeof(t_data));
	if (my_mlx == NULL)
		return (NULL);
	my_mlx->mlx_ptr = mlx_init();
	my_mlx->mlx_img = mlx_new_image(my_mlx->mlx_ptr, 800, 600);
	my_mlx->addr = mlx_get_data_addr(my_mlx->mlx_img, &my_mlx->bpp, &my_mlx->line_length, &my_mlx->endian);
	put_pixel(my_mlx, 10, 10, 255);
	put_square(my_mlx, 100, 50, 50, 255);
	put_square(my_mlx, 100, 100, 75, 255 * 255 * 255);
	put_square(my_mlx, 300, 250, 99, 255 * 255);
	put_square(my_mlx, 750, 550, 49, 255);
	my_mlx->win_ptr = mlx_new_window(my_mlx->mlx_ptr, 800, 600, "miniRT");
	mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr, my_mlx->mlx_img, 0, 0);
	return (my_mlx);
}

int		main(void)
{
	t_data	*my_mlx;

	my_mlx = init_my_mlx();
	mlx_loop(my_mlx->win_ptr);
}
