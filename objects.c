/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/10 22:16:04 by Peer de Bak   ########   odam.nl         */
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
	spherez = my_mlx->sphere->s.z;
	coll = my_mlx->sphere->s.z - my_mlx->sphere->diameter / 2;
	ret = fabs((t1 - spherez) / (coll - spherez));
//	if (ret < 0 || ret > 1)
//		printf("ret=%f, spherez=%f, t1=%f, collision=%f\n", ret, spherez, t1, coll);
	if (ret > 1.0f)
		ret = ret - 1.0f;
	col = colourremap01(my_mlx, ret);
//	printf("col=%lX\n", col);
	return (col);
}

int			find_triangle(t_data *my_mlx)
{
	t_vec3	edge0;
	t_vec3	edge1;
	t_vec3	pvec;
	double	det;

	edge0 = vector_sub(my_mlx->triangle->s1, my_mlx->triangle->s0);
	edge1 = vector_sub(my_mlx->triangle->s2, my_mlx->triangle->s0);
	pvec = crossproduct(my_mlx->ray->v, edge1);
	det = dotproduct(edge0, pvec);

	if (fabs(det) < 0.000001)
		return (0);
	double	invdet = 1 / det;
	t_vec3	tvec = vector_sub(my_mlx->cam->s, my_mlx->triangle->s0);
	double	u = dotproduct(tvec, pvec) * invdet;
	if (u < 0 || u > 1)
		return (0);
	t_vec3	qvec = crossproduct(tvec, edge0);
	double	v = dotproduct(my_mlx->ray->v, qvec) * invdet;
	if (v < 0 || u + v > 1)
		return (0);
	double	t = dotproduct(edge1, qvec) * invdet;
	if (t < my_mlx->ray->length || my_mlx->ray->length == 0)
	{
		my_mlx->ray->length = t;
		my_mlx->ray->colour = my_mlx->triangle->colour;
	}
    return (1); // this ray hits the triangle 
}

int			find_plane(t_data *my_mlx)
{
	t_vec3	sub;
	double	a;
	double	denom;
	double	t;

	sub = vector_sub(my_mlx->plane->s, my_mlx->cam->s);
	denom = dotproduct(my_mlx->plane->normal, my_mlx->ray->v);
	if (denom > 0.000001)
	{
		a = dotproduct(sub, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0)
			if (t < my_mlx->ray->length || my_mlx->ray->length == 0)
			{
				my_mlx->ray->length = t;
				my_mlx->ray->colour = my_mlx->plane->colour;
				return (1);
			}
	}
	return (0);
}

unsigned		find_sphere(t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	double	y;
	double	x;
	double	t1;
	double	t2;
	t_vec3	p;

	tmp = vector_sub(my_mlx->sphere->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	p = vector_add(my_mlx->cam->s, vec_mult(my_mlx->ray->v, t));
	y = find_length(p, my_mlx->sphere->s);
	if (y < my_mlx->sphere->diameter / 2)
	{
		if (pow(my_mlx->sphere->diameter / 2, 2) - (y * y) < 0)
			return (0);
		x = sqrt(pow(my_mlx->sphere->diameter / 2, 2) - pow(y, 2));
		t1 = (t - x);
		t2 = t + x;
		if (t1 < my_mlx->ray->length || my_mlx->ray->length == 0)
		{
			my_mlx->ray->length = t2;
			my_mlx->ray->colour = remap01(my_mlx, t1);
		}
		return (1);
	}
	return (0);
}

unsigned		find_objects(t_data *my_mlx)
{
	t_sphere	*head;
	t_plane		*phead;
	t_triangle	*thead;
	int			ret;

	phead = my_mlx->plane;
	while (my_mlx->plane)
	{
		ret = find_plane(my_mlx);
		my_mlx->plane = my_mlx->plane->next;
	}
	my_mlx->plane = phead;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
		ret = find_sphere(my_mlx);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;

	thead = my_mlx->triangle;
	while (my_mlx->triangle)
	{
		ret = find_triangle(my_mlx);
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle = thead;
	return (ret);
}
