/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/31 10:58:56 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/31 14:23:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sqr(double n)
{
	return (n * n);
}

void	normalize_ray(t_data *my_mlx, double canvasx, double canvasy, double canvasz)
{
	double	length;

	my_mlx->ray->x = canvasx - my_mlx->cam->x;
	my_mlx->ray->y = canvasy - my_mlx->cam->y;
	my_mlx->ray->z = canvasz - my_mlx->cam->z;
	length = sqrt(sqr(my_mlx->ray->x) + sqr(my_mlx->ray->y) + sqr(my_mlx->ray->z));
//	printf("OLD: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->x, my_mlx->ray->y, my_mlx->ray->z, length);
	my_mlx->ray->x /= length;
	my_mlx->ray->y /= length;
	my_mlx->ray->z /= length;
	length = sqrt(sqr(my_mlx->ray->x) + sqr(my_mlx->ray->y) + sqr(my_mlx->ray->z));
//	printf("NEW: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->x, my_mlx->ray->y, my_mlx->ray->z, length);
}

void	ray(t_data *my_mlx, double canvasx, double canvasy, double canvasz)
{
	normalize_ray(my_mlx, canvasx, canvasy, canvasz);
	// trace ray along vector

	// find intersection
	// put pixel in that colour
	// clear my ray variables && return

}
