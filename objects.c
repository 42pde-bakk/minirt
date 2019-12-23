/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/23 18:44:12 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_square(t_data *my_mlx, int x, int y, int size, int color)
{
	int i;
	int x1;
	int y1;

	i = 0;
	y1 = y;
	while (y1 < y + size)
	{
		x1 = x;
		while (x1 < x + size)
		{
			put_pixel(my_mlx, x1, y1, color);
			x1++;
		}
		y1++;
	}
}
