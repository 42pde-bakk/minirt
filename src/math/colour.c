/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 12:06:55 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/05 19:24:52 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	unsigned_to_tcol(unsigned col)
{
	t_col	out;

	out.r = (col >> 16 & 0xff);
	out.g = (col >> 8 & 0xff);
	out.b = (col & 0xff);
	return (out);
}

t_col	colour_new(double r, double g, double b)
{
	t_col ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
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

t_col	colour_div(t_col col, int div)
{
	col.r = col.r / div;
	col.g = col.g / div;
	col.b = col.b / div;
	return (col);
}

t_col	colour_mul(t_col coloura, t_col colourb, double mul)
{
	t_col	ret;

	ret.r = coloura.r * (colourb.r * mul / 255);
	ret.g = coloura.g * (colourb.g * mul / 255);
	ret.b = coloura.b * (colourb.b * mul / 255);
	return (ret);
}
