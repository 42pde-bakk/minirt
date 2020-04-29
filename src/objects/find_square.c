/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_square.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:30 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:14:31 by peer          ########   odam.nl         */
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
