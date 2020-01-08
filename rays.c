/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:01:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/08 15:15:42 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	normalize_ray(double *ray)
{
	double	length;

// 	length = sqrt(pow(my_mlx->ray->v[0], 2) + pow(my_mlx->ray->v[1], 2) + pow(my_mlx->ray->v[2], 2));
// //	printf("OLD: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
// 	my_mlx->ray->v[0] /= length;
// 	my_mlx->ray->v[1] /= length;
// 	my_mlx->ray->v[2] /= length;
// 	length = sqrt(pow(my_mlx->ray->v[0], 2) + pow(my_mlx->ray->v[1], 2) + pow(my_mlx->ray->v[2], 2));
//	printf("NEW: x=%f, y=%f, z=%f, l=%f\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2], length);
	length = sqrt((ray[0] * ray[0]) + (ray[1] * ray[1]) + (ray[2] * ray[2]));
	ray[0] /= length;
	ray[1] /= length;
	ray[2] /= length;
}


double	ndcx(t_data *my_mlx, double x)
{
	double	pixelndcx;
	double	pixelscreenx;
	double	pixelcamerax;
	double	ratio;
	double	angle;

	ratio = my_mlx->scene->width / my_mlx->scene->height;

	pixelndcx = (x + 0.5) / my_mlx->scene->width; //define pixel in NDC space
	pixelscreenx = 2 * pixelndcx - 1; //remap pixel
	angle = my_mlx->cam->fov * (M_PI / 180);
	pixelcamerax = pixelscreenx * ratio * tan(angle / 2);
	return (pixelcamerax);
}

double	ndcy(t_data *my_mlx, double y)
{
	double	pixelndcy;
	double	pixelscreeny;
	double	pixelcameray;
	double	angle;

	pixelndcy = (y + 0.5) / my_mlx->scene->height;
	pixelscreeny = 1 - 2 * pixelndcy;
	angle = my_mlx->cam->fov * (M_PI / 180);
	pixelcameray = pixelscreeny * tan(angle / 2);
	return (pixelcameray);
}

void	fire_ray(t_data *my_mlx, double pndcx, double pndcy)
{
	static int counter;

	my_mlx->ray->v[0] = pndcx;
	my_mlx->ray->v[1] = pndcy;
	my_mlx->ray->v[2] = 1.0f;
//	if (counter % 50 == 0)
//		printf("ray= {%f, %f, %f}\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2]);
	counter++;
}

void	ray(t_data *my_mlx)
{
	double		x = 0;
	double		y = 0;
	double		pndcx;
	double		pndcy;
	unsigned	ret;

//	loopspheres(my_mlx);
//	printf("pndcx=%f, pndcy=%f\n", ndcx(my_mlx, x), ndcy(my_mlx, y));
	while (y < my_mlx->scene->height)
	{
		pndcy = ndcy(my_mlx, y);
//		printf("pndcy=%f\n", pndcy);
		while (x < my_mlx->scene->width)
		{
			pndcx = ndcx(my_mlx, x);
			fire_ray(my_mlx, pndcx, pndcy);
			normalize_ray(my_mlx->ray->v);
//			printf("pndcx, pndcy= (%f, %f)\n", pndcx, pndcy);
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
//	printf("pndcx=%f, pndcy=%f\n", ndcx(my_mlx, x), ndcy(my_mlx, y));
}
