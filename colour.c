/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 12:06:55 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/15 17:31:27 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_col		colour_mult(t_col col, double c1, double c2)
{
	col.r *= c1 * c2;
	col.g *= c1 * c2;
	col.b *= c1 * c2;
	return (col);
}

t_col		coltimescol(t_col a, t_col b)
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

t_col	col_times_lightratio(t_col col, t_col light, double max)
{
	t_col	ret;
	
	ret.r = col.r + (light.r / max);
	ret.g = col.g + (light.g / max);
	ret.b = col.b + (light.b / max);
	return (ret);
}

t_col	colour_mul(t_col coloura, t_col colourb, double mul)
{
	t_col	ret;

	ret.r = coloura.r * colourb.r * mul / 255;
	ret.g = coloura.g * colourb.g * mul / 255;
	ret.b = coloura.b * colourb.b * mul / 255;
	return (ret);
}