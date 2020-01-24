/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/23 23:28:50 by pde-bakk      ########   odam.nl         */
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

// int			triangle_intersection(t_triangle tri, t_data *my_mlx)
// {
// 	t_vec3	edge0;
// 	t_vec3	edge1;
// 	t_vec3	pvec;
// 	double	det;
// 	double	invdet;
// 	t_vec3	tvec;
	

// 	edge0 = vec3_sub(tri.s1, tri.s0);
// 	edge1 = vec3_sub(tri.s2, tri.s0);
// 	pvec = crossproduct(my_mlx->ray->v, edge1);
// 	det = dotproduct(edge0, pvec);

// 	if (fabs(det) < EPSILON)
// 		return (0);
	
// }

t_triangle	tri_rev(t_triangle t)
{
	t_triangle	out;

	out = t;
	out.s0 = t.s2;
	out.s2 = t.s0;
	return (out);
}

int			find_square(t_data *my_mlx)
{
	t_triangle	tri2;
	t_triangle	tri3;

	tri2 = tri_rev(my_mlx->square->tri[0]);
	tri3 = tri_rev(my_mlx->square->tri[1]);

	if (find_triangle(&my_mlx->square->tri[0], my_mlx) == 1)
	{
		return (1);
	}
	else if (find_triangle(&my_mlx->square->tri[1], my_mlx) == 1)
		return (1);
	else if (find_triangle(&tri2, my_mlx) == 1)
		return (1);
	else if (find_triangle(&tri3, my_mlx) == 1)
		return (0);
	else
		return (0);
}

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
			if (t < my_mlx->ray->length || my_mlx->ray->length == 0)
			{
				my_mlx->ray->length = t;
				my_mlx->ray->colour = my_mlx->plane->colour;
				my_mlx->ray->hitnormal = my_mlx->plane->normal;
				return (1);
			}
	}
	return (0);
}

// int		find_cylinder(t_data *my_mlx)
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;

// 	// R(t) = o + td
// 	// x² + z² = r²
// 	// (ox+tdx)² + (oz+tdz)² = r²
// 	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
// 	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
// 	// a=(dx + dz); b = 2(oxdx + ozdz); c = (ox)² + (oz)² - r²

// 	a = pow(my_mlx->ray->v.x, 2) + pow(my_mlx->ray->v.z, 2);
// 	b = 2 * pow(my_mlx->ray->v.x, 2) + 2 * pow(my_mlx->ray->v.y, 2);
// 	c = a - 1;
// 	discriminant = pow(b, 2) - (4 * a * c);

// }

int		visualize_lightsource(t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	double	x;
	double	y;
	double	t1;
	double	t2;
	t_vec3	p;

	tmp = vec3_sub(my_mlx->light->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	if (t < 0)
		return (0);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, t));
	y = find_length(p, my_mlx->light->s);
	if (y < 1)
	{
		if (pow(2, 2) - (y * y) < 0)
			return (0);
		x = sqrt(pow(1, 2) - pow(y, 2));
		t1 = (t - x);
		t2 = t + x;
		if (t1 < my_mlx->ray->length || my_mlx->ray->length == 0)
		{
			if (my_mlx->cam->s.z > t1 * my_mlx->ray->v.z)
				my_mlx->ray->length = t2;
			else
				my_mlx->ray->length = t1;
			my_mlx->ray->colour = my_mlx->light->colour;
			// my_mlx->ray->hitnormal = vec3_sub(my_mlx->sphere->s, vec3_mult(my_mlx->ray->v, t1));
			// my_mlx->ray->hitnormal = vec3_normalize(my_mlx->ray->hitnormal);
		}
		return (1);
	}
	return (0);	
}

int		find_sphere(t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	double	y;
	double	x;
	double	t1;
	double	t2;
	t_vec3	p;

	tmp = vec3_sub(my_mlx->sphere->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	if (t < 0)
		return (0);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, t));
	y = find_length(p, my_mlx->sphere->s);
	if (y < my_mlx->sphere->diameter / 2)
	{
		if (pow(my_mlx->sphere->diameter / 2, 2) - (y * y) < 0)
			return (0);
		x = sqrt(pow(my_mlx->sphere->diameter / 2, 2) - pow(y, 2));
		t1 = (t - x);
		t2 = t + x;
		if (t1 < my_mlx->ray->length || my_mlx->ray->length == 0)
		{
			if (my_mlx->cam->s.z > t1 * my_mlx->ray->v.z)
				my_mlx->ray->length = t2;
			else
				my_mlx->ray->length = t1;
			my_mlx->ray->colour = my_mlx->sphere->colour;
			my_mlx->ray->hitnormal = vec3_sub(my_mlx->sphere->s, vec3_mult(my_mlx->ray->v, t1));
			my_mlx->ray->hitnormal = vec3_normalize(my_mlx->ray->hitnormal);
		}
		return (1);
	}
	return (0);
}

int		find_objects(t_data *my_mlx)
{
	t_sphere	*head;
	t_plane		*phead;
	t_triangle	*thead;
	t_square	*shead;
	t_light		*lighthead;
	int			ret;

	lighthead = my_mlx->light;
	while (my_mlx->light)
	{
		ret = visualize_lightsource(my_mlx);
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = lighthead;
	
	phead = my_mlx->plane;
	while (my_mlx->plane)
	{
		ret = find_plane(my_mlx);
		my_mlx->plane = my_mlx->plane->next;
	}
	my_mlx->plane = phead;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
		ret = find_sphere(my_mlx);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;

	thead = my_mlx->triangle;
	while (my_mlx->triangle)
	{
		ret = find_triangle(my_mlx->triangle, my_mlx);
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle = thead;

	shead = my_mlx->square;
	while (my_mlx->square)
	{
		ret = find_square(my_mlx);
		my_mlx->square = my_mlx->square->next;
	}
	my_mlx->square = shead;
	return (ret);
}
