/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 12:06:55 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/21 20:27:26 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_col	colour_mul(t_col coloura, t_col colourb, double mul)
{
	t_col	ret;

	ret.r = coloura.r * (colourb.r * mul / 255);
	ret.g = coloura.g * (colourb.g * mul / 255);
	ret.b = coloura.b * (colourb.b * mul / 255);
	return (ret);
}

t_col	colour_cap(t_col colour)
{
	colour.r = fmin(colour.r, 255);
	colour.g = fmin(colour.g, 255);
	colour.b = fmin(colour.b, 255);
	return (colour);
}

int		colour_check(t_col colour)
{
	if (colour.r < 0.0 || colour.r > 255.0)
		return (0);
	if (colour.g < 0.0 || colour.g > 255.0)
		return (0);
	if (colour.b < 0.0 || colour.b > 255.0)
		return (0);
	return (1);
}
