/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/04 15:38:23 by pde-bakk      ########   odam.nl         */
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

unsigned long			colourremap01(t_data *my_mlx, double ret)
{
	int	r;
	int	g;
	int	b;
	unsigned long col;

	col = my_mlx->sphere->colour;
//	printf("colour=%lX\n", col);
	r = (col >> 16 & 0xff); // 255.0;
	g = (col >> 8 & 0xff); // 255.0;
	b = (col & 0xff); // 255.0;
//	printf("rgb= %i, %i, %i\n", r, g, b);
	r *= ret;
	g *= ret;
	b *= ret;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned long			remap01(t_data *my_mlx, double t1)
{
	double	a;
	double	b;
	double	ret;
	unsigned long	col;

	t1 = fabs(t1);
	a = my_mlx->sphere->s[2];
	b = my_mlx->sphere->s[2] - my_mlx->sphere->diameter / 2;
	ret = fabs((t1 - a) / (b - a));
	if (ret < 0 || ret > 1)
		printf("ret=%f, a=%f\n", ret, a);
	col = colourremap01(my_mlx, ret);
//	printf("col=%lX\n", col);
	return (col);
}

unsigned long		find_sphere(t_data *my_mlx)
{
	double	*tmp;
	double	*tmpt;
	double	t;
	double	t1;
	double	t2;
	double	y;
	double	x;

	tmp = vector_subtractor(my_mlx->sphere->s, my_mlx->cam->s);
//	printf("diameter=%f\n", my_mlx->sphere->diameter);
//	printf("tmp[]={%f, %f, %f}\n", tmp[0], tmp[1], tmp[2]);
	t = dotproduct(tmp, my_mlx->ray->v);
	free(tmp);
	tmpt = doublemapi(my_mlx->ray->v, t);
//	printf("tmpt={%f, %f, %f}\n", tmpt[0], tmpt[1], tmpt[2]);
//	printf("ray={%f, %f, %f}\n", my_mlx->ray->v[0], my_mlx->ray->v[1], my_mlx->ray->v[2]);
	my_mlx->ray->p = vector_add(my_mlx->cam->s, tmpt);
	free(tmpt);
	y = find_length(my_mlx->sphere->s, my_mlx->ray->p);
	if (y < my_mlx->sphere->diameter / 2)
	{
		x = sqrt(pow(my_mlx->sphere->diameter / 2, 2) - pow(y, 2));
		t1 = fabs(t - x);
//		t2 = t + x;
		my_mlx->ray->length = t1;
		my_mlx->ray->colour = remap01(my_mlx, t1);
		return (1);
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
//		printf("new sphere met diameter=%f\n", my_mlx->sphere->diameter);
		ret =  find_sphere(my_mlx);
		if (ret > 0)
		{
			my_mlx->sphere = head;
			return (ret);
		}
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;
	return (0);
}
