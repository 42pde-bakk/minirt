/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 12:06:55 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/15 12:21:33 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// unsigned			colourremap01(t_data *my_mlx, double ret)
// {
// 	int				r;
// 	int				g;
// 	int				b;
// 	unsigned		col;

// 	col = my_mlx->ray->colour;
// 	r = (col >> 16 & 0xff);
// 	g = (col >> 8 & 0xff);
// 	b = (col & 0xff);
// 	r *= ret;
// 	g *= ret;
// 	b *= ret;
// 	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
// }

t_vec3			unsigned_to_vec(unsigned col)
{
	t_vec3	vec;

	vec.x = (col >> 16 & 0xff);
	vec.y = (col >> 8 & 0xff);
	vec.z = (col & 0xff);
	return (vec);
}

unsigned		vec_to_unsigned(t_vec3 vec)
{
	int	r;
	int	g;
	int b;

	r = (int)vec.x;
	g = (int)vec.y;
	b = (int)vec.z;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int		plane_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	double	a;
	double	denom;
	double	t;

	tmp = vector_sub(my_mlx->plane->s, pos);
	denom = dotproduct(my_mlx->plane->normal, dir);
	if (denom > 0.000001)
	{
		a = dotproduct(tmp, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0)
			return (1);
	}
	return (0);
}

int		sphere_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	t_vec3	p;
	double	t;
	double	y;

	tmp = vector_sub(my_mlx->sphere->s, pos);
	t = dotproduct(dir, my_mlx->ray->v);
	p = vector_add(pos, vec_mult(dir, t));
	y = find_length(p, my_mlx->sphere->s);
	if (y < my_mlx->sphere->diameter / 2)
		return (1);
	else
		return (0);
}

t_col		colour_mult(t_col col, double c1, double c2)
{
	col.r *= c1 * c2;
	col.g *= c1 * c2;
	col.b *= c1 * c2;
	return (col);
}

t_col		colour_multcol(t_col a, t_col b)
{
	t_col	out;

	out.r = a.r * b.r;
	out.g = a.g * b.g;
	out.b = a.b * b.b;
	return (out);
}

t_col	colour_new(void)
{
	t_col ret;

	ret.r = 0.f;
	ret.g = 0.f;
	ret.b = 0.f;
	return (ret);	
}

t_col	colour_add(t_col v1, t_col v2)
{
	t_col	ret;

	ret.r = v1.r + v2.r;
	ret.g = v1.g + v2.g;
	ret.b = v1.b + v2.b;
	return (ret);
}

t_col	colour_check(t_col col)
{
	col.r = fmin(255.f, col.r);
	col.g = fmin(255.f, col.g);
	col.b = fmin(255.f, col.b);
	return (col);
}