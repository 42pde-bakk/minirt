/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_sphere_square.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:17:53 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:17:54 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double				click_sphere(t_sphere *sp, t_data *my_mlx, t_vec3 ray)
{
	double	t0;
	t_vec3	p;
	double	y;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), ray);
	if (t0 < 0)
		return (-1);
	p = vec3_add(my_mlx->cam->s, vec3_mult(ray, t0));
	y = find_length(p, sp->s);
	if (y > sp->diameter / 2 || y < 0 || pow(sp->diameter / 2, 2) - y * y < 0)
		return (-1);
	return (t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2)));
}

static t_trihelp	tri_calc(t_triangle *tri, t_data *my_mlx, t_vec3 ray)
{
	t_trihelp	th;

	th.edge0 = vec3_sub(tri->s1, tri->s0);
	th.edge1 = vec3_sub(tri->s2, tri->s0);
	th.pvec = crossproduct(ray, th.edge1);
	th.det = dotproduct(th.edge0, th.pvec);
	th.invdet = 1 / th.det;
	th.tvec = vec3_sub(my_mlx->cam->s, tri->s0);
	th.u = dotproduct(th.tvec, th.pvec) * th.invdet;
	th.qvec = crossproduct(th.tvec, th.edge0);
	th.v = dotproduct(ray, th.qvec) * th.invdet;
	th.t = dotproduct(th.edge1, th.qvec) * th.invdet;
	return (th);
}

double				click_triangle(t_triangle *tri, t_data *my_mlx, t_vec3 ray)
{
	t_trihelp	th;

	th = tri_calc(tri, my_mlx, ray);
	if (th.det > 0 || fabs(th.det) < EPSILON ||
		th.u < 0 || th.u > 1 || th.v < 0 || th.u + th.v > 1)
		return (-1);
	return (th.t);
}

double				click_square(t_square *sq, t_data *my_mlx, t_vec3 ray)
{
	double		distance1;
	double		distance2;
	double		distance1rev;
	double		distance2rev;
	t_triangle	rev;

	distance1 = click_triangle(&sq->tri[0], my_mlx, ray);
	distance2 = click_triangle(&sq->tri[1], my_mlx, ray);
	rev = tri_rev(sq->tri[0]);
	distance1rev = click_triangle(&rev, my_mlx, ray);
	rev = tri_rev(sq->tri[1]);
	distance2rev = click_triangle(&rev, my_mlx, ray);
	if (distance1 < 0.0 && distance1rev >= 0.0)
		distance1 = distance1rev;
	if (distance2 < 0.0 && distance2rev >= 0.0)
		distance2 = distance2rev;
	if (distance1 >= 0.0 && (distance1 <= distance2 || distance2 < 0.0))
		return (distance1);
	else if (distance2 >= 0.0 && (distance2 <= distance1 || distance1 < 0.0))
		return (distance2);
	else
		return (-1);
}
