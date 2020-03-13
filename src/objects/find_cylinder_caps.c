/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder_caps.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 19:28:06 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/13 19:39:58 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_cylinder_caps(t_data *my_mlx, t_cylinder *cyl, int threadnr, t_vec3 pos)
{
	t_vec3	sub;
	double	denom;
	double	a;
	double	t;

	sub = vec3_sub(pos, my_mlx->cam->s);
	denom = dotproduct(cyl->v, my_mlx->ray[threadnr]->v);
	if (denom > EPSILON)
	{
		a = dotproduct(sub, cyl->v);
		t = a / denom;
		if (find_length(pos, vec3_mult(my_mlx->ray[threadnr]->v, t))
				<= cyl->diameter / 2)
		{
			if (t < my_mlx->ray[threadnr]->length)
			{
				my_mlx->ray[threadnr]->length = t;
				my_mlx->ray[threadnr]->colour = cyl->colour;
				my_mlx->ray[threadnr]->hitnormal = cyl->v;
			}
		}
	}
	return (1);
}
