/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_triangle.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:36 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:14:37 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_trihelp	tri_calc(t_triangle *tri, t_data *my_mlx, int threadnr)
{
	t_trihelp	th;

	th.edge0 = vec3_sub(tri->s1, tri->s0);
	th.edge1 = vec3_sub(tri->s2, tri->s0);
	th.pvec = crossproduct(my_mlx->ray[threadnr]->v, th.edge1);
	th.det = dotproduct(th.edge0, th.pvec);
	th.invdet = 1 / th.det;
	th.tvec = vec3_sub(my_mlx->cam->s, tri->s0);
	th.u = dotproduct(th.tvec, th.pvec) * th.invdet;
	th.qvec = crossproduct(th.tvec, th.edge0);
	th.v = dotproduct(my_mlx->ray[threadnr]->v, th.qvec) * th.invdet;
	th.t = dotproduct(th.edge1, th.qvec) * th.invdet;
	return (th);
}

int					triangle_intersect(t_triangle *tri, t_data *my_mlx,
		int threadnr)
{
	t_trihelp	th;

	th = tri_calc(tri, my_mlx, threadnr);
	if (th.det > 0 || fabs(th.det) < EPSILON ||
		th.u < 0 || th.u > 1 || th.v < 0 || th.u + th.v > 1)
		return (0);
	if (th.t < my_mlx->ray[threadnr]->length && th.t > 0)
	{
		my_mlx->ray[threadnr]->length = th.t;
		my_mlx->ray[threadnr]->colour = tri->colour;
		my_mlx->ray[threadnr]->hitnormal = tri->normal;
		return (1);
	}
	return (0);
}

t_triangle			tri_rev(t_triangle t)
{
	t_triangle	out;

	out = t;
	out.s0 = t.s2;
	out.s2 = t.s0;
	return (out);
}

int					find_triangle(t_triangle *tri, t_data *my_mlx, int threadnr)
{
	if (triangle_intersect(tri, my_mlx, threadnr) == 1)
		return (1);
	else
		return (0);
}
