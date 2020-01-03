/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/03 14:25:33 by pde-bakk      ########   odam.nl         */
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
	while (/*v1[i] && v2[i] &&*/ i < 3)
	{
		ret[i] = v1[i] - v2[i];
		i++;
//		printf("vector_subtractor gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret[i]);
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
	while (/*v1[i] && v2[i] &&*/ i < 3)
	{
		ret[i] = v1[i] + v2[i];
//		printf("vector_add gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret[i]);
		i++;
	}
	return (ret);
}

double	dotproduct(double *v1, double *v2)
{
	int		i;
	double	ret;

	ret = 0.0;
	i = 0;
	while (/*v1[i] && v2[i] &&*/i < 3)
	{
		ret += v1[i] * v2[i];
//		printf("dotproduct gives: {%f, %f, result=%f}\n", v1[i], v2[i], ret);
		i++;
	}
//	printf("ehhe\n");
	return (ret);
}

double	*double_x_v(double *v1, double d)
{
	int	i;
	double	*ret;

	i = 0;
	ret = (double*)malloc(sizeof(double) * 4);
	if (!ret)
		return (NULL);
	while (/*v1[i] && */i < 3)
	{
		ret[i] = v1[i] * d;
		i++;
	}
	return (ret);
}

double	find_length(double *s, double *p)
{
	double	ret;
	double	retx;
	double	rety;
	double	retz;

	retx = pow(s[0] - p[0], 2);
	rety = pow(s[1] - p[1], 2);
	retz = pow(s[2] - p[2], 2);
	ret = sqrt(retx + rety + retz);
	return (ret);

}

unsigned long		find_sphere(t_data *my_mlx)
{
	double	*tmp;
	double	*tmpt;
	double	t;
	double	t1;
	double t2;
	double	y;
	double	x;

	tmp = vector_subtractor(my_mlx->sphere->s, my_mlx->cam->s);
//	printf("tmp[]={%f, %f, %f}\n", tmp[0], tmp[1], tmp[2]);
	t = dotproduct(tmp, my_mlx->ray->v);
	free(tmp);
	tmpt = double_x_v(my_mlx->ray->v, t);
//	printf("tmpt={%f, %f, %f}\n", tmpt[0], tmpt[1], tmpt[2]);
//	printf("ray={%f, %f, %f}\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2]);
	my_mlx->ray->p = vector_add(my_mlx->cam->s, tmpt);
	y = find_length(my_mlx->sphere->s, my_mlx->ray->p);
	if (y < my_mlx->sphere->diameter / 2)
	{
		x = sqrt(pow(my_mlx->sphere->diameter / 2, 2) - pow(y, 2));
		t1 = t - x;
		t2 = t + x;
		return (my_mlx->sphere->colour);
	}
//	printf("t=%f\n", my_mlx->ray->t);
//	printf("p={%f, %f, %f}\n", my_mlx->ray->p[0], my_mlx->ray->p[1], my_mlx->ray->p[2]);
	return (0);
}

unsigned long		find_objects(t_data *my_mlx)
{
	t_sphere	*head;
	unsigned long	ret;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
//		printf("new sphere\n");
		ret = find_sphere(my_mlx);
		if (ret > 0)
			return (ret);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;
	return (0);
}
