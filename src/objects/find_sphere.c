/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sphere.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:07:20 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 13:02:08 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	sphere_intersect(t_sphere *sp, t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	t_vec3	p;

	tmp = vec3_sub(sp->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	if (t < 0)
		return (-1);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, t));
	return (find_length(p, sp->s));
}

int				find_sphere(t_sphere *sp, t_data *my_mlx)
{
	double	y;
	double	t0;
	double	t1;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), my_mlx->ray->v);
	y = sphere_intersect(sp, my_mlx);
	if (y < sp->diameter / 2 && y >= 0)
	{
		if (pow(sp->diameter / 2, 2) - (y * y) < 0)
			return (0);
		t1 = t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2));
		if (t1 < my_mlx->ray->length)
		{
			my_mlx->ray->length = t1;
			my_mlx->ray->colour = sp->colour;
			my_mlx->ray->hitnormal = vec3_sub(vec3_mult(my_mlx->ray->v,
			my_mlx->ray->length), sp->s);
			my_mlx->ray->hitnormal = vec3_mult(my_mlx->ray->hitnormal, -1);
			my_mlx->ray->hitnormal = vec3_normalize(my_mlx->ray->hitnormal);
		}
		return (1);
	}
	return (0);
}
