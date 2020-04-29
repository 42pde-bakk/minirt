/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:25:42 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:25:44 by peer          ########   odam.nl         */
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
