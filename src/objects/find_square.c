/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_square.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:32 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/11 23:47:45 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_square(t_square *sq, t_data *my_mlx, int threadnr)
{
	if (find_triangle(&sq->tri[0], my_mlx, threadnr) == 1)
	{
		return (1);
	}
	else if (find_triangle(&sq->tri[1], my_mlx, threadnr) == 1)
	{
		return (1);
	}
	else
		return (0);
}
