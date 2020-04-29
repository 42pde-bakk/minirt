/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newframe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 19:22:55 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 18:10:16 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		newframe(t_data *my_mlx)
{
	ray(my_mlx);
	if (my_mlx->bmp == 1)
	{
		bmp(my_mlx);
		freemachine(my_mlx);
		return (0);
	}
	mlx_clear_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
	if (my_mlx->frame % 2 == 0)
		mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr,
			my_mlx->mlx_img, 0, 0);
	else
		mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr,
			my_mlx->mlx_img2, 0, 0);
	my_mlx->frame++;
	mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr, 0, 10, WHITE,
	"use wasd for movement, q&e for up/down");
	mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr, 0, 20, WHITE,
	"arrowkeys for camera rotation");
	return (1);
}
