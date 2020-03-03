/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:07:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/03 17:30:43 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	filter_sepia(t_col in)
{
	t_col	out;

	out.r = (in.r * 0.393) + (in.g * 0.769) + (in.b * 0.189);
	out.g = (in.r * 0.349) + (in.g * 0.686) + (in.b * 0.168);
	out.b = (in.r * 0.272) + (in.g * 0.534) + (in.b * 0.131);
	return (out);
}

#if BONUS == 1 && SEPIA == 1

void	put_rgb(t_data *my_mlx, int x, int y, t_col rgb)
{
	int	pos;
	int	r;
	int g;
	int b;

	r = (int)(filter_sepia(rgb).r);
	g = (int)(filter_sepia(rgb).g);
	b = (int)(filter_sepia(rgb).b);
	if (x >= 0 && x < my_mlx->scene->width && y >= 0 &&
		y < my_mlx->scene->height)
	{
		pos = y * my_mlx->line_length + x * (my_mlx->bpp / 8);
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

#else

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

#endif
