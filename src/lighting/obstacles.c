/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:26:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/11 15:59:36 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	obstaclecheck(t_data *my_mlx, t_vec3 hitpos, t_vec3 lightdir,
		double distance)
{
	lightdir = vec3_normalize(lightdir);
	if (triangles_loopover(my_mlx, hitpos, lightdir, distance) == 1)
		return (1);
	if (squares_loopover(my_mlx, hitpos, lightdir, distance) == 1)
		return (1);
	if (cylinders_loopover(my_mlx, hitpos, lightdir, distance) == 1)
		return (1);
	if (spheres_loopover(my_mlx, hitpos, lightdir, distance) == 1)
		return (1);
	if (planes_loopover(my_mlx, hitpos, lightdir, distance) == 1)
		return (1);
	return (0);
}
