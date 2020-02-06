/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_properties.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 01:29:43 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/06 01:36:18 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		sphere_edit_properties(t_data *my_mlx, double distancex, double distancey)
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
	my_mlx->sphere->s = vec3_sub(my_mlx->sphere->s, vec3_mult(my_mlx->cam->c2w.r, distancex * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->sphere->s = vec3_sub(my_mlx->sphere->s, vec3_mult(my_mlx->cam->c2w.up, distancey * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->sphere = spherehead;
	return (1);
}

int		triangle_edit_properties(t_data *my_mlx, double distancex, double distancey)
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
	my_mlx->triangle->s0 = vec3_sub(my_mlx->triangle->s0, vec3_mult(my_mlx->cam->c2w.r, distancex * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s0 = vec3_sub(my_mlx->triangle->s0, vec3_mult(my_mlx->cam->c2w.up, distancey * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle->s1 = vec3_sub(my_mlx->triangle->s1, vec3_mult(my_mlx->cam->c2w.r, distancex * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s1 = vec3_sub(my_mlx->triangle->s1, vec3_mult(my_mlx->cam->c2w.up, distancey * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle->s2 = vec3_sub(my_mlx->triangle->s2, vec3_mult(my_mlx->cam->c2w.r, distancex * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s2 = vec3_sub(my_mlx->triangle->s2, vec3_mult(my_mlx->cam->c2w.up, distancey * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle = trianglehead;
	return (1);
}

