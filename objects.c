/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/08 20:55:57 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned			colourremap01(t_data *my_mlx, double ret)
{
	int				r;
	int				g;
	int				b;
	unsigned		col;

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
	unsigned	col;

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

unsigned		find_triangle(t_data *my_mlx)
{
	double	d;
	double	*p;
	double	t;
	double	pc; //parallelcheck

	p = NULL;
	trianglecross(my_mlx, my_mlx->triangle->cross);
	normalize_ray(my_mlx->triangle->cross);
	d = dotproduct(my_mlx->triangle->cross, my_mlx->triangle->s1);
	pc = dotproduct(my_mlx->triangle->cross, my_mlx->ray->v);
	if (pc == 0) // if the normal of the triangle * the ray direction = 0
		return (0);
	t = -(dotproduct(my_mlx->triangle->cross, my_mlx->cam->s) + d) / pc;
	//t=-(dot(N, orig) + D / dot(N, dir))
	p = vector_add(my_mlx->cam->s, (doublemapi(my_mlx->ray->v, t, p)), p);
	return (0);
}

unsigned		find_sphere(t_data *my_mlx)
{
	double	*tmp;
	double	t;
	double	t1;
	double	t2;
	double	y;
	double	x;

	tmp = vector_subtractor(my_mlx->sphere->s, my_mlx->cam->s, my_mlx->sphere->tmp);
//	printf("tmp={%f, %f, %f} while struct={%f, %f, %f}\n", tmp[0], tmp[1], tmp[2], my_mlx->sphere->tmp[0], my_mlx->sphere->tmp[1], my_mlx->sphere->tmp[2]);
	t = dotproduct(tmp, my_mlx->ray->v);

	tmp = doublemapi(my_mlx->ray->v, t, my_mlx->sphere->tmp);
	tmp = vector_add(my_mlx->cam->s, tmp, my_mlx->ray->p);

	y = find_length(my_mlx->sphere->s, my_mlx->ray->p);
	if (y < my_mlx->sphere->diameter / 2)
	{
		x = sqrt(pow(my_mlx->sphere->diameter / 2, 2) - pow(y, 2));
		t1 = (t - x);
		t2 = t + x;
		if (t1 < my_mlx->ray->length || my_mlx->ray->length == 0)
		{
			my_mlx->ray->length = t1;
			my_mlx->ray->colour = remap01(my_mlx, t1);
		}
		return (1);
	}
//	printf("t=%f\n", my_mlx->ray->t);
//	printf("p={%f, %f, %f}\n", my_mlx->ray->p[0], my_mlx->ray->p[1], my_mlx->ray->p[2]);
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
