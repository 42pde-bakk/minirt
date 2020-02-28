/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:07:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/28 13:25:53 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_rgb(t_data *my_mlx, int x, int y, t_col rgb)
{
	int	pos;
	int	r;
	int g;
	int b;

	r = (int)rgb.r;
	g = (int)rgb.g;
	b = (int)rgb.b;
	if (x >= 0 && x < my_mlx->scene->width && y >= 0 &&
		y < my_mlx->scene->height)
	{
		pos = y * my_mlx->line_length + x * (my_mlx->bpp / 8);
		// printf("xy=[%d, %d],    pos=%d\n", x, y, pos);
		if (my_mlx->frame % 2 == 0)
		{
			*(my_mlx->addr + pos + 0) = (char)(b);
			*(my_mlx->addr + pos + 1) = (char)(g);
			*(my_mlx->addr + pos + 2) = (char)(r);
		}
		else if (my_mlx->frame % 2 == 1)
		{
			*(my_mlx->addr2 + pos + 0) = (char)(b);
			*(my_mlx->addr2 + pos + 1) = (char)(g);
			*(my_mlx->addr2 + pos + 2) = (char)(r);
		}
	}
}
