/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_triangle.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:48 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 20:31:36 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_trihelp	tri_calc(t_triangle *tri, t_data *my_mlx)
{
	t_trihelp	th;

	th.edge0 = vec3_sub(tri->s1, tri->s0);
	th.edge1 = vec3_sub(tri->s2, tri->s0);
	th.pvec = crossproduct(my_mlx->ray->v, th.edge1);
	th.det = dotproduct(th.edge0, th.pvec);
	th.invdet = 1 / th.det;
	th.tvec = vec3_sub(my_mlx->cam->s, tri->s0);
	th.u = dotproduct(th.tvec, th.pvec) * th.invdet;
	th.qvec = crossproduct(th.tvec, th.edge0);
	th.v = dotproduct(my_mlx->ray->v, th.qvec) * th.invdet;
	th.t = dotproduct(th.edge1, th.qvec) * th.invdet;
	return (th);
}

int					triangle_intersect(t_triangle *tri, t_data *my_mlx)
{
	t_trihelp	th;

	th = tri_calc(tri, my_mlx);
	if (th.det > 0 || fabs(th.det) < EPSILON ||
		th.u < 0 || th.u > 1 || th.v < 0 || th.u + th.v > 1)
		return (0);
	if (th.t < my_mlx->ray->length && th.t > 0)
	{
		my_mlx->ray->length = th.t;
		my_mlx->ray->colour = tri->colour;
		my_mlx->ray->hitnormal = tri->normal;
	}
	return (1);
}

t_triangle			tri_rev(t_triangle t)
{
	t_triangle	out;

	out = t;
	out.s0 = t.s2;
	out.s2 = t.s0;
	return (out);
}

int					find_triangle(t_triangle *tri, t_data *my_mlx)
{
	if (triangle_intersect(tri, my_mlx) == 1)
		return (1);
	else
		return (0);
}
