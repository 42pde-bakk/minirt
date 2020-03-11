/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_uvimg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:09:51 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/11 17:13:01 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_uvimg(t_data *my_mlx)
{
	if (UV == 1)
		my_mlx->uvimg = mlx_png_file_to_image(my_mlx->mlx_ptr,
					"textures/pic.png", &my_mlx->uvnx, &my_mlx->uvny);
	else
		my_mlx->uvimg = mlx_png_file_to_image(my_mlx->mlx_ptr,
					"textures/world.png", &my_mlx->uvnx, &my_mlx->uvny);
	my_mlx->uvaddr = mlx_get_data_addr(my_mlx->uvimg, &my_mlx->uvbpp,
		&my_mlx->uvll, &my_mlx->uvendian);
}
