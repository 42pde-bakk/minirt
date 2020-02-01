/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/01 17:49:42 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wasd(int keycode, t_data *my_mlx)
{
	t_vec3	movement;

	movement = vec3_new(0.0, 0.0, 0.0);
	if ((keycode >= AKEY && keycode <= DKEY) || (keycode >= QKEY && keycode <= EKEY))
	{
		printmatrix(my_mlx->cam->c2w);
		printf("\n");
		//	movement = vec3_add(movement, vec3_new(0.0, MOVE_SPEED, 0.0));
		if (keycode == WKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.fw, MOVE_SPEED));
		if (keycode == AKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.r, MOVE_SPEED));
		if (keycode == SKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.fw, MOVE_SPEED));
		if (keycode == DKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.r, MOVE_SPEED));
		if (keycode == QKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.up, MOVE_SPEED));
		if (keycode == EKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->cam->c2w.up, MOVE_SPEED));
		//my_mlx->cam->s = vec3_add(my_mlx->cam->s, pleurmatrix(movement, my_mlx->cam->c2w));
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
		my_mlx->cam->v = addrotation(my_mlx->cam->v, adjust);
		my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s, vec3_add(my_mlx->cam->s, my_mlx->cam->v));
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
		// (void)my_mlx;
		free(my_mlx->mlx_img);
		free(my_mlx->mlx_ptr);
		exit(0);
	}
	return (1);
}

int	ripwindow(t_data *my_mlx)
{
	free(my_mlx->mlx_img);
	free(my_mlx->mlx_img2);
	free(my_mlx->mlx_ptr);
	exit(0);
}

int		mouseinput(int mlxhook, t_data *my_mlx)
{
	static int	hidemouse;

	if (mlxhook == 17)
	{
		free(my_mlx->mlx_img);
		free(my_mlx->mlx_ptr);
		exit(0);
	}
	if (mlxhook == MOUSE_PRESS_HOOK)
	{
		if (hidemouse % 2 == 0)
			mlx_mouse_show();
		else
			mlx_mouse_show();
		hidemouse++;		
		return (0);
	}
	return (1);
}
