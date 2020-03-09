/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sphere.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:07:20 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/03 19:01:41 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	sphere_intersect(t_sphere *sp, t_data *my_mlx, int threadnr)
{
	t_vec3	tmp;
	double	t;
	t_vec3	p;

	tmp = vec3_sub(sp->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray[threadnr]->v);
	if (t < 0)
		return (-1);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v, t));
	return (find_length(p, sp->s));
}

#if BONUS == 1 && UV == 1

int				find_sphere(t_sphere *sp, t_data *my_mlx, int threadnr)
{
	double	y;
	double	t0;
	double	t1;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), my_mlx->ray[threadnr]->v);
	y = sphere_intersect(sp, my_mlx, threadnr);
	if (y < sp->diameter / 2 && y >= 0)
	{
		if (pow(sp->diameter / 2, 2) - (y * y) < 0)
			return (0);
		t1 = t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2));
		if (t1 < my_mlx->ray[threadnr]->length)
		{
			my_mlx->ray[threadnr]->length = t1;
			my_mlx->ray[threadnr]->colour = uvmapping(my_mlx, sp, threadnr);
			my_mlx->ray[threadnr]->hitnormal = vec3_sub(vec3_mult(
		my_mlx->ray[threadnr]->v, my_mlx->ray[threadnr]->length), sp->s);
			my_mlx->ray[threadnr]->hitnormal =
				vec3_normalize(vec3_mult(my_mlx->ray[threadnr]->hitnormal, -1));
		}
		return (1);
	}
	return (0);
}

#elif BONUS == 1 && UV == 0

int				find_sphere(t_sphere *sp, t_data *my_mlx, int threadnr)
{
	double	y;
	double	t0;
	double	t1;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), my_mlx->ray[threadnr]->v);
	y = sphere_intersect(sp, my_mlx, threadnr);
	if (y <= sp->diameter / 2 && y >= 0)
	{
		if (pow(sp->diameter / 2, 2) - (y * y) < 0)
			return (0);
		t1 = t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2));
		if (t1 < my_mlx->ray[threadnr]->length)
		{
			my_mlx->ray[threadnr]->length = t1;
			my_mlx->ray[threadnr]->colour = uv_checkers(my_mlx, sp, threadnr);
			my_mlx->ray[threadnr]->hitnormal = vec3_sub(vec3_mult(
		my_mlx->ray[threadnr]->v, my_mlx->ray[threadnr]->length), sp->s);
			my_mlx->ray[threadnr]->hitnormal =
				vec3_normalize(vec3_mult(my_mlx->ray[threadnr]->hitnormal, -1));
		}
		return (1);
	}
	return (0);
}

#else

int				find_sphere(t_sphere *sp, t_data *my_mlx, int threadnr)
{
	double	y;
	double	t0;
	double	t1;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), my_mlx->ray[threadnr]->v);
	y = sphere_intersect(sp, my_mlx, threadnr);
	if (y < sp->diameter / 2 && y >= 0)
	{
		if (pow(sp->diameter / 2, 2) - (y * y) < 0)
			return (0);
		t1 = t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2));
		if (t1 < my_mlx->ray[threadnr]->length)
		{
			my_mlx->ray[threadnr]->length = t1;
			my_mlx->ray[threadnr]->colour = sp->colour;
			my_mlx->ray[threadnr]->hitnormal = vec3_sub(vec3_mult(
		my_mlx->ray[threadnr]->v, my_mlx->ray[threadnr]->length), sp->s);
			my_mlx->ray[threadnr]->hitnormal =
				vec3_normalize(vec3_mult(my_mlx->ray[threadnr]->hitnormal, -1));
		}
		return (1);
	}
	return (0);
}

#endif
