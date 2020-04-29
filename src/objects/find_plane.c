/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_plane.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:08 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:14:09 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			find_plane(t_plane *pl, t_data *my_mlx, int threadnr)
{
	t_vec3	sub;
	double	a;
	double	denom;
	double	t;

	sub = vec3_sub(pl->s, my_mlx->cam->s);
	denom = dotproduct(pl->normal, my_mlx->ray[threadnr]->v);
	if (denom > EPSILON)
	{
		a = dotproduct(sub, pl->normal);
		t = a / denom;
		if (t > 0)
			if (t < my_mlx->ray[threadnr]->length)
			{
				my_mlx->ray[threadnr]->length = t;
				my_mlx->ray[threadnr]->colour = pl->colour;
				my_mlx->ray[threadnr]->hitnormal = vec3_mult(pl->normal, -1);
				return (1);
			}
	}
	return (0);
}
