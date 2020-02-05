/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_square.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:32 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/04 19:56:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_square(t_data *my_mlx)
{
	if (find_triangle(&my_mlx->square->tri[0], my_mlx) == 1)
		return (1);
	else if (find_triangle(&my_mlx->square->tri[1], my_mlx) == 1)
		return (1);
	else
		return (0);
}
