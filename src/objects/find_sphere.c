/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sphere.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:07:20 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/29 17:49:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		find_sphere(t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	double	y;
	double	x;
	double	t1;
	double	t2;
	t_vec3	p;

	tmp = vec3_sub(my_mlx->sphere->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	if (t < 0)
		return (0);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, t));
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
			if (my_mlx->cam->s.z > t1 * my_mlx->ray->v.z)
				my_mlx->ray->length = t2;
			else
				my_mlx->ray->length = t1;
			my_mlx->ray->colour = my_mlx->sphere->colour;
			my_mlx->ray->hitnormal = vec3_sub(vec3_mult(my_mlx->ray->v, my_mlx->ray->length), my_mlx->sphere->s);
			my_mlx->ray->hitnormal = vec3_normalize(my_mlx->ray->hitnormal);
		}
		return (1);
	}
	return (0);
}
