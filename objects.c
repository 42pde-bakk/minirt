/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/02 19:10:18 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_square(t_data *my_mlx, int x, int y, int size, int color)
{
	int i;
	int x1;
	int y1;

	i = 0;
	y1 = y;
	while (y1 < y + size)
	{
		x1 = x;
		while (x1 < x + size)
		{
			put_pixel(my_mlx, x1, y1, color);
			x1++;
		}
		y1++;
	}
}

double	*vector_subtractor(double *v1, double *v2)
{
	int		i;
	double	*ret;

	i = 0;
	ret = (double*)malloc(sizeof(double) * 4);
	if (!ret)
		return (NULL);
	while (v1[i] && v2[i] && i < 3)
	{
		ret[i] = v1[i] - v2[i];
		i++;
	}
	return (ret);
}

double	*vector_add(double *v1, double *v2)
{
	int		i;
	double	*ret;

	i = 0;
	ret = (double*)malloc(sizeof(double) * 4);
	if (!ret)
		return (NULL);
	while (v1[i] && v2[i] && i < 3)
	{
		ret[i] = v1[i] + v2[i];
		i++;
	}
	return (ret);
}

double	dotproduct(double *v1, double *v2)
{
	int		i;
	double	ret;

	i = 0;
	ret = 0;
	while (v1[i] && v2[i] && i < 3)
	{
		ret += v1[i] * v2[i];
		i++;
		printf("dot\n");
	}
	printf("ehhe\n");
	return (ret);
}

double	*double_x_v(double *v1, double d)
{
	int	i;

	i = 0;
	while (v1[i] && i < 3)
	{
		v1[i] = v1[i] * d;
		i++;
	}
	return (v1);
}

int		find_sphere(t_data *my_mlx)
{
	double	*tmp;

	tmp = vector_subtractor(my_mlx->sphere->s, my_mlx->cam->s); //letog
	my_mlx->ray->t = dotproduct(tmp, my_mlx->ray->v);
	my_mlx->ray->p = vector_add(my_mlx->cam->s, double_x_v(my_mlx->ray->v, my_mlx->ray->t));
	printf("t=%f\n", my_mlx->ray->t);
	printf("p={%f, %f, %f}\n", my_mlx->ray->p[0], my_mlx->ray->p[1], my_mlx->ray->p[2]);
//	px = pixelx + t * my_mlx->ray->x;
//	py = pixely + t * my_mlx->ray->y;
//	pz = pixelz + t * my_mlx->ray->z;
/*
	y = length(s - p);
	if (y < r)
	{
		x = sqrt(pow(my_mlx->sphere->diameter/2) - y*y);
		t1 = t - x;
		t2 = t+ x;
	}
*/
	return (0);
}

int		find_objects(t_data *my_mlx)
{
	while (my_mlx->sphere)
	{
		printf("new sphere\n");
		find_sphere(my_mlx);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	return (0);
}
