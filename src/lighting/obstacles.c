/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:26:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/13 20:20:26 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	obstacle_check(t_data *my_mlx, t_vec3 hitpos, t_vec3 lightdir)
// {
// 	void *tmp;

// 	tmp = my_mlx->plane;
// 	while (tmp)
// 	{
// 		if (obstacle_plane((t_plane*)tmp, my_mlx, hitpos, lightdir) == 1)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	tmp = my_mlx->sphere;
// 	while (tmp)
// 	{
// 		if (obstacle_sphere((t_sphere*)tmp, my_mlx, hitpos, lighdir) == 1)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
