/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_triangle.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:48 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:07:01 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			find_triangle(t_triangle *tri, t_data *my_mlx)
{
	t_vec3	edge0;
	t_vec3	edge1;
	t_vec3	pvec;
	double	det;

	edge0 = vec3_sub(tri->s1, tri->s0);
	edge1 = vec3_sub(tri->s2, tri->s0);
	pvec = crossproduct(my_mlx->ray->v, edge1);
	det = dotproduct(edge0, pvec);
	if (det > 0)
		return (0);
	if (fabs(det) < EPSILON)
		return (0);
	double	invdet = 1 / det;
	t_vec3	tvec = vec3_sub(my_mlx->cam->s, tri->s0);
	double	u = dotproduct(tvec, pvec) * invdet;
	if (u < 0 || u > 1)
		return (0);
	t_vec3	qvec = crossproduct(tvec, edge0);
	double	v = dotproduct(my_mlx->ray->v, qvec) * invdet;
	if (v < 0 || u + v > 1)
		return (0);
	double	t = dotproduct(edge1, qvec) * invdet;
	if (t < my_mlx->ray->length || my_mlx->ray->length == 0)
	{
		my_mlx->ray->length = t;
		my_mlx->ray->colour = tri->colour;
		my_mlx->ray->hitnormal = tri->normal;
	}
    return (1); // this ray hits the triangle 
}
