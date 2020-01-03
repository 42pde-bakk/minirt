/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/31 10:58:56 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/03 14:26:18 by pde-bakk      ########   odam.nl         */
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

	my_mlx->ray->v[0] = canvasx - my_mlx->cam->s[0];
	my_mlx->ray->v[1] = canvasy - my_mlx->cam->s[1];
	my_mlx->ray->v[2] = canvasz - my_mlx->cam->s[2];
	length = sqrt(sqr(my_mlx->ray->v[0]) + sqr(my_mlx->ray->v[1]) + sqr(my_mlx->ray->v[2]));
//	printf("OLD: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
	my_mlx->ray->v[0] /= length;
	my_mlx->ray->v[1] /= length;
	my_mlx->ray->v[2] /= length;
	length = sqrt(sqr(my_mlx->ray->v[0]) + sqr(my_mlx->ray->v[1]) + sqr(my_mlx->ray->v[2]));
//	printf("NEW: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
}

void	ray(t_data *my_mlx, double canvasx, double canvasy, double canvasz)
{
	int		x;
	int		y;
	unsigned long	ret;
//	printf("welcome\n");

	x = 0;
	y = 0;
	while (canvasy < my_mlx->cam->canvy2)
	{
//		printf("canvasy=%f\n", canvasy);
		canvasx = my_mlx->cam->canvx1;
		while (canvasx < my_mlx->cam->canvx2)
		{
			normalize_ray(my_mlx, canvasx, canvasy, canvasz);
			ret = find_objects(my_mlx);
			if (ret > 0)
				put_pixel(my_mlx, x, y, ret);
			canvasx++;
			x++;
		}
		canvasy++;
		y++;
	}
	// trace ray along vector

	// find intersection
	// put pixel in that colour
	// clear my ray variables && return

}
