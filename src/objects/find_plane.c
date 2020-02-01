/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_plane.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:05 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/30 15:48:13 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			find_plane(t_data *my_mlx)
{
	t_vec3	sub;
	double	a;
	double	denom;
	double	t;

	sub = vec3_sub(my_mlx->plane->s, my_mlx->cam->s);
	denom = dotproduct(my_mlx->plane->normal, my_mlx->ray->v);
	if (denom > 0.000001)
	{
		a = dotproduct(sub, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0)
			if (t < my_mlx->ray->length)
			{
				my_mlx->ray->length = t;
				my_mlx->ray->colour = my_mlx->plane->colour;
				my_mlx->ray->hitnormal = my_mlx->plane->normal;
				return (1);
			}
	}
	return (0);
}
