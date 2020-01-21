/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/21 22:29:30 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wasd(int keycode, t_data *my_mlx)
{
	if (keycode == AKEY)
	{
		my_mlx->cam->s.x = my_mlx->cam->s.x - 5.0;
		printf("X-5: %f\n", my_mlx->cam->s.x);
		newframe(my_mlx);
	}
	if (keycode == DKEY)
	{
		my_mlx->cam->s.x = my_mlx->cam->s.x + 5.0;
		printf("X-5: %f\n", my_mlx->cam->s.x);
		newframe(my_mlx);
	}
	if (keycode == WKEY)
	{
		my_mlx->cam->s.y = my_mlx->cam->s.y + 5.0;
		printf("Y+5: %f\n", my_mlx->cam->s.y);
		newframe(my_mlx);
	}
	if (keycode == SKEY)
	{
		my_mlx->cam->s.y = my_mlx->cam->s.y - 5.0;
		printf("Y-5: %f\n", my_mlx->cam->s.y);
		newframe(my_mlx);
	}
	if (keycode == QKEY)
	{
		my_mlx->cam->s.z = my_mlx->cam->s.z + 5.0;
		printf("Z+5: %f\n", my_mlx->cam->s.z);
		newframe(my_mlx);
	}
	if (keycode == EKEY)
	{
		my_mlx->cam->s.z = my_mlx->cam->s.z - 5.0;
		printf("Z-5: %f\n", my_mlx->cam->s.z);
		newframe(my_mlx);
	}
}

void	arrowkeys(int keycode, t_data *my_mlx)
{
	t_vec3		adjust;

	adjust = vec3_new(0.0, 0.0, 0.0);
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW || keycode == UP_ARROW
		|| keycode == DOWN_ARROW || keycode == NUMZERO || keycode == NUMONE)
	{
		if (keycode == LEFT_ARROW)
			adjust = vec3_sub(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
		if (keycode == RIGHT_ARROW)
			adjust = vec3_add(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
		if (keycode == UP_ARROW)
			adjust = vec3_add(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == DOWN_ARROW)
			adjust = vec3_sub(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMONE)
			adjust = vec3_add(adjust, vec3_new(0.0, 0.0, CAM_ROT_SPEED));
		if (keycode == NUMZERO)
			adjust = vec3_sub(adjust, vec3_new(0.0, 0.0, CAM_ROT_SPEED));
		my_mlx->cam->c2w = ft_newrotate(my_mlx, adjust);
		newframe(my_mlx);
	}
}

void	swapcameras(int keycode, t_data *my_mlx)
{
	if (keycode == PLUS)
	{
		if (my_mlx->cam->next == NULL)
			my_mlx->cam = my_mlx->camhead;
		else
			my_mlx->cam = my_mlx->cam->next;
		newframe(my_mlx);
	}	
}

int		keyinput(int keycode, t_data *my_mlx)
{
	wasd(keycode, my_mlx);
	arrowkeys(keycode, my_mlx);
	swapcameras(keycode, my_mlx);
	if (keycode == ESCAPE)
	{
		(void)my_mlx;
		free(my_mlx->mlx_img);
		free(my_mlx->mlx_ptr);
		exit(0);
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