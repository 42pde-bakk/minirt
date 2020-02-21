/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacle_square.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:09:48 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/19 19:12:13 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	obstacle_square(t_square *sq, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	if (obstacle_triangle(&sq->tri[0], hitpos, lightdir, distance) == 1)
		return (1);
	else if (obstacle_triangle(&sq->tri[1], hitpos, lightdir, distance) == 1)
		return (1);
	return (0);
}

int	squares_loopover(t_data *my_mlx, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	t_square	*tmpsquare;

	tmpsquare = my_mlx->square;
	while (tmpsquare)
	{
		if (obstacle_square(tmpsquare, hitpos, lightdir, distance) == 1)
			return (1);
		tmpsquare = tmpsquare->next;
	}
	return (0);
}
