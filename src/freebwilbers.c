/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freebwilbers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 22:29:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/12 18:39:09 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	freeplane(void *in)
{
	t_plane *tmp;
	t_plane *plane;

	plane = (t_plane*)in;
	while (plane)
	{
		tmp = plane->next;
		free(plane);
		plane = tmp;
	}
}

int	freemachine(t_data *my_mlx)
{
	freeplane(my_mlx->plane);
	freeplane(my_mlx->sphere);
	freeplane(my_mlx->square);
	freeplane(my_mlx->triangle);
	freeplane(my_mlx->cylinder);
	freeplane(my_mlx->light);
	free(my_mlx->scene);
	free(my_mlx->ray);
	free(my_mlx->click);
	free(my_mlx->mlx_img);
	free(my_mlx->mlx_img2);
	free(my_mlx->mlx_ptr);
	free(my_mlx);
	exit(0);
}
