/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newframe.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 19:22:55 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 23:25:39 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	newframe_setup(t_data *my_mlx, void **imgptr, char **imgaddr)
{
	mlx_destroy_image(my_mlx->mlx_ptr, *imgptr);
	*imgptr = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width,
	my_mlx->scene->height);
	*imgaddr = mlx_get_data_addr(*imgptr, &my_mlx->bpp, &my_mlx->line_length,
	&my_mlx->endian);
	printf("ray\n");
	ray(my_mlx);
	printf("ray2\n");
	mlx_clear_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
	mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr, *imgptr, 0, 0);
}

int		newframe(t_data *my_mlx)
{
	printf("newframe\n");
	if (my_mlx->frame % 2 == 0)
	{
		newframe_setup(my_mlx, &my_mlx->mlx_img, &my_mlx->addr);
	}
	else if (my_mlx->frame % 2 == 1)
	{
		newframe_setup(my_mlx, &my_mlx->mlx_img2, &my_mlx->addr2);
	}
	my_mlx->frame++;
	printf("frame\n");
	mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr, 0, 10, WHITE,
	"use wasd for movement, q&e for up/down");
	mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr, 0, 20, WHITE,
	"arrowkeys for camera rotation");
	return (1);
}
