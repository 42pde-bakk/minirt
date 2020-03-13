/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_props2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 16:37:09 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/13 13:10:20 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cylinder_edit_properties(t_data *my_mlx)
{
	t_cylinder	*cylinderhead;
	int			i;

	i = 0;
	cylinderhead = my_mlx->cylinder;
	while (i < my_mlx->click->index && my_mlx->cylinder)
	{
		i++;
		my_mlx->cylinder = my_mlx->cylinder->next;
	}
	my_mlx->cylinder->v = my_mlx->click->rotation;
	my_mlx->cylinder->s = obj_move(my_mlx->cylinder->s, my_mlx);
	my_mlx->cylinder->height *= my_mlx->click->heightmult;
	my_mlx->cylinder->diameter *= my_mlx->click->sizemult;
	my_mlx->cylinder = cylinderhead;
	return (1);
}

int	sphere_edit_properties(t_data *my_mlx)
{
	t_sphere	*spherehead;
	int			i;

	i = 0;
	spherehead = my_mlx->sphere;
	while (i < my_mlx->click->index && my_mlx->sphere)
	{
		i++;
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere->s = obj_move(my_mlx->sphere->s, my_mlx);
	my_mlx->sphere->diameter *= my_mlx->click->sizemult;
	my_mlx->sphere = spherehead;
	return (1);
}

int	plane_edit_properties(t_data *my_mlx)
{
	t_plane	*planehead;
	int		i;

	i = 0;
	planehead = my_mlx->plane;
	while (i < my_mlx->click->index && my_mlx->plane)
	{
		i++;
		my_mlx->plane = my_mlx->plane->next;
	}
	my_mlx->plane->s = my_mlx->click->rotation;
	my_mlx->plane->s = obj_move(my_mlx->plane->s, my_mlx);
	my_mlx->plane = planehead;
	return (1);
}
