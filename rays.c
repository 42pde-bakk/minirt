/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:01:34 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/04 18:22:24 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_ray(t_data *my_mlx)
{
	double	length;

	length = sqrt(pow(my_mlx->ray->v[0], 2) + pow(my_mlx->ray->v[1], 2) + pow(my_mlx->ray->v[2], 2));
	printf("OLD: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
	my_mlx->ray->v[0] /= length;
	my_mlx->ray->v[1] /= length;
	my_mlx->ray->v[2] /= length;
	length = sqrt(pow(my_mlx->ray->v[0], 2) + pow(my_mlx->ray->v[1], 2) + pow(my_mlx->ray->v[2], 2));
	printf("NEW: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
}

double	ndcx(t_data *my_mlx, double x)
{
	double	PixelNDCx;
	double	PixelScreenx;
	double	PixelCamerax;
	double	angle;

	PixelNDCx = (x + 0.5) / my_mlx->scene->width; // define pixel in NDC space

	PixelScreenx = 2 * PixelNDCx - 1; // pixel remapped

	if (my_mlx->scene->width > my_mlx->scene->height)
	{
		PixelCamerax = 2 * PixelNDCx - 1;
		PixelCamerax *= (my_mlx->scene->width / my_mlx->scene->height);
	}
	else
		PixelCamerax = PixelScreenx;
	angle = my_mlx->cam->fov * (M_PI / 180);
	PixelCamerax = PixelCamerax * tan(angle / 2);
	return (PixelCamerax);

}

double	ndcy(t_data *my_mlx, double y)
{
	double	PixelNDCy;
	double	PixelScreeny;
	double	PixelCameray;
	double	angle;

	PixelNDCy = (y + 0.5) / my_mlx->scene->height;

	PixelScreeny = 1 - 2 * PixelNDCy;
//	if (my_mlx->scene->height > my_mlx->scene->width)
//	{
//		PixelCameray = 2 * PixelScreeny - 1;
//		PixelCameray *= (my_mlx->scene->height / my_mlx->scene->width);
//	}
//	else
	PixelCameray = PixelScreeny;
	angle = my_mlx->cam->fov * (M_PI / 180);
	PixelCameray = PixelCameray * tan(angle / 2);
	return (PixelCameray);
}

void	fire_ray(t_data *my_mlx, double pndcx, double pndcy)
{
	my_mlx->ray->v[0] = pndcx;
	my_mlx->ray->v[1] = pndcy;
	my_mlx->ray->v[2] = -1.0f;
}

void	ray(t_data *my_mlx)
{
	double	x = 0;
	double	y = 0;
	double	pndcx;
	double	pndcy;
	unsigned long	ret;

	loopspheres(my_mlx);
	while (y < my_mlx->scene->height)
	{
		pndcy = ndcy(my_mlx, y);
//		printf("pndcy=%f\n", pndcy);
		while (x < my_mlx->scene->width)
		{
			pndcx = ndcx(my_mlx, x);
			fire_ray(my_mlx, pndcx, pndcy);
//			printf("pndcx, pndcy= (%f, %f)\n", pndcx, pndcy);
//			normalize_ray(my_mlx);
			ret = find_objects(my_mlx);
			if (my_mlx->ray->length > 0)
			{
				put_pixel(my_mlx, x, y, my_mlx->ray->colour);
				my_mlx->ray->length = 0;
				my_mlx->ray->colour = 0;
			}
//			printf("pndcx=%f\n", pndcx);
			x++;
		}
		y++;
		x = 0;
	}
	// trace ray along vector

	// find intersection
	// put pixel in that colour
	// clear my ray variables && return

}
