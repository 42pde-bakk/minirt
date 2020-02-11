/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_plane.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:05 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 16:06:19 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			find_plane(t_plane *pl, t_data *my_mlx)
{
	t_vec3	sub;
	double	a;
	double	denom;
	double	t;

	sub = vec3_sub(pl->s, my_mlx->cam->s);
	denom = dotproduct(pl->normal, my_mlx->ray->v);
	if (denom > 0.000001)
	{
		a = dotproduct(sub, pl->normal);
		t = a / denom;
		if (t > 0)
			if (t < my_mlx->ray->length)
			{
				my_mlx->ray->length = t;
				my_mlx->ray->colour = pl->colour;
				my_mlx->ray->hitnormal = vec3_mult(pl->normal, -1);
				return (1);
			}
	}
	return (0);
}
