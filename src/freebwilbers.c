/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freebwilbers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 22:29:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/24 14:35:35 by pde-bakk      ########   odam.nl         */
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

int		freemachine(t_data *my_mlx)
{
	static int	check = 0;

	if (check > 0)
		return (0);
	check++;
	freeplane(my_mlx->plane);
	freeplane(my_mlx->sphere);
	freeplane(my_mlx->square);
	freeplane(my_mlx->triangle);
	freeplane(my_mlx->cylinder);
	freeplane(my_mlx->light);
	free(my_mlx->scene);
	free(my_mlx->ray);
	free(my_mlx->click);
	mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img);
	mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img2);
	if (my_mlx->win_ptr != NULL)
		mlx_destroy_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
	free(my_mlx->mlx_img);
	free(my_mlx->mlx_img2);
	// free(my_mlx->mlx_ptr);
	// free(my_mlx->win_ptr);
	// system("leaks miniRT"); //remove pls
	exit(0);
}
