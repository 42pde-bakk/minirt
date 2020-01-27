/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_square.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:32 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:06:40 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
