/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacle_triangle.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:10:56 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/19 19:30:00 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_trihelp	tri_calc(t_triangle *tri, t_vec3 lightdir, t_vec3 hitpos)
{
	t_trihelp	th;

	th.edge0 = vec3_sub(tri->s1, tri->s0);
	th.edge1 = vec3_sub(tri->s2, tri->s0);
	th.pvec = crossproduct(lightdir, th.edge1);
	th.det = dotproduct(th.edge0, th.pvec);
	th.invdet = 1 / th.det;
	th.tvec = vec3_sub(hitpos, tri->s0);
	th.u = dotproduct(th.tvec, th.pvec) * th.invdet;
	th.qvec = crossproduct(th.tvec, th.edge0);
	th.v = dotproduct(lightdir, th.qvec) * th.invdet;
	th.t = dotproduct(th.edge1, th.qvec) * th.invdet;
	return (th);
}

int					obstacle_triangle(t_triangle *tri, t_vec3 hitpos,
						t_vec3 lightdir, double distance)
{
	t_trihelp th;

	th = tri_calc(tri, lightdir, hitpos);
	if (th.det > 0 || fabs(th.det) < EPSILON ||
		th.u < 0 || th.u > 1 || th.v < 0 || th.u + th.v > 1)
		return (0);
	if (th.t > 0.0 && th.t < distance)
		return (1);
	return (0);
}

int					triangles_loopover(t_data *my_mlx, t_vec3 hitpos,
						t_vec3 lightdir, double distance)
{
	t_triangle	*tmptriangle;

	tmptriangle = my_mlx->triangle;
	while (tmptriangle)
	{
		if (obstacle_triangle(tmptriangle, hitpos, lightdir, distance) == 1)
			return (1);
		tmptriangle = tmptriangle->next;
	}
	return (0);
}
