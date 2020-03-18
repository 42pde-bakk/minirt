/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder_caps.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 19:28:06 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/18 15:20:12 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_cylinder_caps(t_data *my_mlx, t_cylinder *cyl, int threadnr, t_vec3 pos)
{
	double	denom;
	t_vec3	p0l0;
	double	t;
	t_vec3	p;
	t_vec3	v;
	double	d2;

	cyl->v = vec3_mult(cyl->v, -1.0);
	denom = dotproduct(cyl->v, my_mlx->ray[threadnr]->v);
	if (denom > EPSILON)
	{
		p0l0 = vec3_sub(cyl->s, my_mlx->cam->s);
		t = dotproduct(p0l0, cyl->v) / denom;
		if (t > 0)
		{
			p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v, t));
			v = vec3_sub(p, cyl->s);
			d2 = dotproduct(v, v);
			if (d2 < pow(cyl->diameter / 2, 2))
				if (t < my_mlx->ray[threadnr]->length)
				{
					my_mlx->ray[threadnr]->length = t;
					my_mlx->ray[threadnr]->hitnormal = cyl->v;
					my_mlx->ray[threadnr]->colour = colour_new(255, 255, 255);
				}
		}
	}
	return (1);
}
