/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:01:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/17 23:34:29 by Peer de Bak   ########   odam.nl         */
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
		if (my_mlx->frame % 2 == 1)
		{
			*(my_mlx->addr + pos + 0) = (char)(b);
			*(my_mlx->addr + pos + 1) = (char)(g);
			*(my_mlx->addr + pos + 2) = (char)(r);
		}
		else if (my_mlx->frame % 2 == 0)
		{
			*(my_mlx->addr2 + pos + 0) = (char)(b);
			*(my_mlx->addr2 + pos + 1) = (char)(g);
			*(my_mlx->addr2 + pos + 2) = (char)(r);
		}
	}
}

double	ndcx(t_data *my_mlx, double x)
{
	double	pixelx;
	double	ratio;
	double	angle;

	ratio = my_mlx->scene->width / my_mlx->scene->height;

	pixelx = (x + 0.5) / my_mlx->scene->width; //define pixel in NDC space
	pixelx = 2 * pixelx - 1; //remap pixel
	angle = my_mlx->cam->fov * (M_PI / 180);
	pixelx = pixelx * ratio * tan(angle / 2);
	return (pixelx);
}

double	ndcy(t_data *my_mlx, double y)
{
	double	pixely;
	double	angle;

	pixely = (y + 0.5) / my_mlx->scene->height;
	pixely = 1 - 2 * pixely;
	angle = my_mlx->cam->fov * (M_PI / 180);
	pixely *= tan(angle / 2);
	return (pixely);
}

void	ray(t_data *my_mlx)
{
	double		x = 0;
	double		y = 0;
	double		pndcx;
	double		pndcy;
	unsigned	ret;

	t_matrix camtoworld = setmatrix(my_mlx);
	while (y < my_mlx->scene->height)
	{
		pndcy = ndcy(my_mlx, y);
		while (x < my_mlx->scene->width)
		{
			pndcx = ndcx(my_mlx, x);
			setcamera(my_mlx, pndcx, pndcy, camtoworld);
			ret = find_objects(my_mlx);
			if (my_mlx->ray->length > 0)
			{
				my_mlx->ray->colour = light_tracing(my_mlx);
				put_rgb(my_mlx, x, y, my_mlx->ray->colour);
				my_mlx->ray->length = 0.0;
				my_mlx->ray->colour = colour_new();
				my_mlx->ray->hitnormal = vec3_new(0.0, 0.0, 0.0);
			}
			x++;
		}
		y++;
		x = 0;
	}
}
