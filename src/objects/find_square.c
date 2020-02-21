/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_square.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:06:32 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/17 21:02:20 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_square(t_square *sq, t_data *my_mlx)
{
	if (find_triangle(&sq->tri[0], my_mlx) == 1)
	{
		// printf("1st triangle\n");
		return (1);
	}
	else if (find_triangle(&sq->tri[1], my_mlx) == 1)
	{
		// printf("2nd triangle\n");
		return (1);
	}
	else
		return (0);
}
