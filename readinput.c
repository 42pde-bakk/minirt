/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/09 15:23:11 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	arrowkeys(int keycode, t_data *my_mlx)
{
	if (keycode == LEFT_ARROW)
	{
		my_mlx->cam->s.x = my_mlx->cam->s.x - 5.0;
		printf("X-5: %f\n", my_mlx->cam->s.x);
		newframe(my_mlx);
	}
	if (keycode == RIGHT_ARROW)
	{
		my_mlx->cam->s.x = my_mlx->cam->s.x + 5.0;
		printf("X-5: %f\n", my_mlx->cam->s.x);
		newframe(my_mlx);
	}
	if (keycode == UP_ARROW)
	{
		my_mlx->cam->s.y = my_mlx->cam->s.y + 5.0;
		printf("Y+5: %f\n", my_mlx->cam->s.y);
		newframe(my_mlx);
	}
	if (keycode == DOWN_ARROW)
	{
		my_mlx->cam->s.y = my_mlx->cam->s.y - 5.0;
		printf("Y-5: %f\n", my_mlx->cam->s.y);
		newframe(my_mlx);
	}
}

int		keyinput(int keycode, t_data *my_mlx)
{
	arrowkeys(keycode, my_mlx);
	if (keycode == ESCAPE)
	{
		(void)my_mlx;
		free(my_mlx->mlx_img);
		free(my_mlx->mlx_ptr);
		exit(0);
	}
	if (keycode == NUMONE)
	{
		my_mlx->cam->s.z = my_mlx->cam->s.z + 5.0;
		printf("Z+5: %f\n", my_mlx->cam->s.z);
		newframe(my_mlx);
	}
	if (keycode == NUMZERO)
	{
		my_mlx->cam->s.z = my_mlx->cam->s.z - 5.0;
		printf("Z-5: %f\n", my_mlx->cam->s.z);
		newframe(my_mlx);
	}
	return (1);
}

int		mouseinput(int keycode, t_data *my_mlx)
{
	if (keycode == LEFT_CLICK)
	{
		printf("Newframe\n");
		my_mlx->win_ptr = my_mlx->win_ptr;
//		newframe(my_mlx);
	}
	return (1);
}