/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:07:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/06 12:54:59 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col			filter_sepia(t_col in)
{
	t_col	out;

	out.r = (in.r * 0.393) + (in.g * 0.769) + (in.b * 0.189);
	out.g = (in.r * 0.349) + (in.g * 0.686) + (in.b * 0.168);
	out.b = (in.r * 0.272) + (in.g * 0.534) + (in.b * 0.131);
	return (out);
}

unsigned int	get_transp(t_col rgb, int stereoscopy)
{
	int				r;
	int				g;
	int				b;
	int				tvalue;

	if (stereoscopy == 1)
	{
		r = fmin(255, fmax(0, (rgb.r - rgb.b) + (rgb.r - rgb.g)));
		g = 0;
		b = 0;
	}
	else
	{
		r = 0;
		g = 0;
		b = fmin(255, fmax(0, (rgb.b - rgb.g) + (rgb.b - rgb.r)));
	}
	tvalue = 200;
	return (((tvalue & 0xff) << 24) + ((r & 0xff) << 16) +
			((g & 0xff) << 8) + (b & 0xff));
}

#if BONUS == 1 && SEPIA == 1

void			put_rgb(t_data *my_mlx, int x, int y, t_col rgb)
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

#elif BONUS == 1 && STEREOSCOPY == 1

void			put_rgb(t_data *my_mlx, int x, int y, t_col rgb)
{
	unsigned int	transp;
	int				pos;

	transp = get_transp(rgb, my_mlx->stereoscopy);
	if (x >= 0 && x < my_mlx->scene->width && y >= 0 &&
		y < my_mlx->scene->height)
	{
		pos = y * my_mlx->line_length + x * (my_mlx->bpp / 8);
		if (my_mlx->stereoscopy == 1)
		{
			if (my_mlx->frame % 2 == 0)
				*(unsigned int*)(my_mlx->addr + pos) = transp;
			else if (my_mlx->frame % 2 == 1)
				*(unsigned int*)(my_mlx->addr2 + pos + 0) = transp;
		}
		else
		{
			if (my_mlx->frame % 2 == 0)
				*(unsigned int*)(my_mlx->addr + pos) += transp;
			else if (my_mlx->frame % 2 == 1)
				*(unsigned int*)(my_mlx->addr2 + pos + 0) += transp;
		}
	}
}

#else

void			put_rgb(t_data *my_mlx, int x, int y, t_col rgb)
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
