/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 17:15:56 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/03 17:16:10 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
