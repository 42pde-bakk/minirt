/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/07 18:39:06 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned			colourremap01(t_data *my_mlx, double ret)
{
	int				r;
	int				g;
	int				b;
	unsigned 		col;

	col = my_mlx->sphere->colour;
	r = (col >> 16 & 0xff);
	g = (col >> 8 & 0xff);
	b = (col & 0xff);
	r *= ret;
	g *= ret;
	b *= ret;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned				remap01(t_data *my_mlx, double t1)
{
	double		spherez;
	double		coll;
	double		ret;
	unsigned 	col;

	t1 = fabs(t1);
	spherez = my_mlx->sphere->s[2];
	coll = my_mlx->sphere->s[2] - my_mlx->sphere->diameter / 2;
	ret = fabs((t1 - spherez) / (coll - spherez));
//	if (ret < 0 || ret > 1)
//		printf("ret=%f, spherez=%f, t1=%f, collision=%f\n", ret, spherez, t1, coll);
	if (ret > 1.0f)
		ret = ret - 1.0f;
	col = colourremap01(my_mlx, ret);
//	printf("col=%lX\n", col);
	return (col);
}

unsigned		find_sphere(t_data *my_mlx)
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
//	printf("cam ={%f, %f, %f}\n", my_mlx->cam->s[0], my_mlx->cam->s[1], my_mlx->cam->s[2]);
//	printf("sphere ={%f, %f, %f}\n", my_mlx->sphere->s[0], my_mlx->sphere->s[1], my_mlx->sphere->s[2]);
//	printf("sphere - cam ={%f, %f, %f}\n", tmp[0], tmp[1], tmp[2]);
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
		t1 = (t - x);
		t2 = t + x;
		if (t1 > my_mlx->ray->length)
		{
			my_mlx->ray->length = t1;
			my_mlx->ray->colour = remap01(my_mlx, t1);
		}
		free(my_mlx->ray->p);
		return (1);
	}
//	printf("t=%f\n", my_mlx->ray->t);
//	printf("p={%f, %f, %f}\n", my_mlx->ray->p[0], my_mlx->ray->p[1], my_mlx->ray->p[2]);
	free(my_mlx->ray->p);
	return (0);
}

unsigned 		find_objects(t_data *my_mlx)
{
	t_sphere	*head;
	int			ret;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
//		printf("new sphere met diameter=%f\n", my_mlx->sphere->diameter);
		ret = find_sphere(my_mlx);
//		printf("ret = %i\n", ret);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;
	return (ret);
}
