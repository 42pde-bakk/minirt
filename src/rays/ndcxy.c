/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ndcxy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:06:55 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 18:12:29 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ndcx(t_data *my_mlx, double x)
{
	double	pixelx;
	double	ratio;
	double	angle;

	ratio = my_mlx->scene->width / my_mlx->scene->height;
	pixelx = (x + 0.5) / my_mlx->scene->width;
	pixelx = 2 * pixelx - 1;
	angle = my_mlx->cam->fov * (M_PI / 180) / 2;
	pixelx = pixelx * ratio * tan(angle);
	return (pixelx);
}

double	ndcy(t_data *my_mlx, double y)
{
	double	pixely;
	double	angle;

	pixely = (y + 0.5) / my_mlx->scene->height;
	pixely = 1 - 2 * pixely;
	angle = my_mlx->cam->fov * (M_PI / 180) / 2;
	pixely *= tan(angle);
	return (pixely);
}
