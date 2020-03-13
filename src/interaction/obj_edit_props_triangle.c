/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_props_triangle.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/13 13:10:09 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/13 13:13:35 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	triangle_edit_back(t_data *my_mlx)
{
	t_triangle	*trianglehead;
	int			i;

	i = 0;
	trianglehead = my_mlx->triangle;
	if (my_mlx->click->index % 2 == 0)
		my_mlx->click->index += 1;
	else
		my_mlx->click->index -= 1;
	while (i < my_mlx->click->index && my_mlx->triangle)
	{
		i++;
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle->s0 = obj_move(my_mlx->triangle->s0, my_mlx);
	my_mlx->triangle->s1 = obj_move(my_mlx->triangle->s1, my_mlx);
	my_mlx->triangle->s2 = obj_move(my_mlx->triangle->s2, my_mlx);
	my_mlx->triangle = trianglehead;
	return (1);
}

int	triangle_edit_properties(t_data *my_mlx)
{
	t_triangle	*trianglehead;
	int			i;

	i = 0;
	trianglehead = my_mlx->triangle;
	while (i < my_mlx->click->index && my_mlx->triangle)
	{
		i++;
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle->s0 = obj_move(my_mlx->triangle->s0, my_mlx);
	my_mlx->triangle->s1 = obj_move(my_mlx->triangle->s1, my_mlx);
	my_mlx->triangle->s2 = obj_move(my_mlx->triangle->s2, my_mlx);
	my_mlx->triangle = trianglehead;
	triangle_edit_back(my_mlx);
	return (1);
}
