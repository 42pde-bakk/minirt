/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 14:59:57 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/22 20:24:10 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_mms_20191025_beta/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include "minirt.h"

typedef struct  s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

/*
t_map	*ft_initmap(void)
{
	t_map	*map;
	map = malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->img = NULL;
	map->addr = 0;
	return (map);
	} */

void	my_mlx_pixel_put(t_data img, int x, int y, int color)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	*(unsigned int*)dst = *(unsigned int*)color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	*img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img->img = mlx_new_image(mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img, &img->bits_per_pixel, &img->line_length, &img->endian);
	my_mlx_pixel_put(*img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
}
