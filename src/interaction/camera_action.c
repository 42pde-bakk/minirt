/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera_action.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 22:11:38 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/17 16:22:37 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wasd(int keycode, t_data *my_mlx)
{
	if (keycode == WKEY || keycode == AKEY || keycode == SKEY ||
		keycode == DKEY || keycode == QKEY || keycode == EKEY)
	{
		if (keycode == WKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.fw, MOVE_SPEED));
		if (keycode == SKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.fw, MOVE_SPEED));
		if (keycode == AKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.r, MOVE_SPEED));
		if (keycode == DKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.r, MOVE_SPEED));
		if (keycode == QKEY)
			my_mlx->cam->s = vec3_sub(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.up, MOVE_SPEED));
		if (keycode == EKEY)
			my_mlx->cam->s = vec3_add(my_mlx->cam->s,
			vec3_mult(my_mlx->cam->c2w.up, MOVE_SPEED));
		my_mlx->click->state = 0;
		newframe(my_mlx);
	}
}

void	camera_rotate(t_data *my_mlx, t_matrix (*f)(double camrot), int lr)
{
	my_mlx->cam->c2w = multmatrix(my_mlx->cam->c2w, f(lr * CAM_ROT_SPEED));
}

void	lookat_zaxis(int keycode, t_data *my_mlx, t_vec3 adjust)
{
	if (keycode != NUMZERO && keycode != NUMONE)
	{
		my_mlx->cam->v = addrotation(my_mlx->cam->v, adjust);
		my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s,
				vec3_add(my_mlx->cam->s, my_mlx->cam->v));
	}
}

void	arrowkeys(int keycode, t_data *my_mlx)
{
	t_vec3	adjust;

	adjust = vec3_new(0.0, 0.0, 0.0);
	if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW || keycode == UP_ARROW
		|| keycode == DOWN_ARROW || keycode == NUMONE || keycode == NUMZERO)
	{
		if (keycode == LEFT_ARROW)
			adjust = vec3_sub(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
		if (keycode == RIGHT_ARROW)
			adjust = vec3_add(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
		if (keycode == DOWN_ARROW)
			adjust = vec3_add(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == UP_ARROW)
			adjust = vec3_sub(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMZERO)
			camera_rotate(my_mlx, &rotate_zaxis, -1);
		if (keycode == NUMONE)
			camera_rotate(my_mlx, &rotate_zaxis, 1);
		lookat_zaxis(keycode, my_mlx, adjust);
		newframe(my_mlx);
	}
}
