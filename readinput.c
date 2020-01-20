/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/20 20:26:49 by pde-bakk      ########   odam.nl         */
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
	t_matrix	angles;

	adjust = vec3_new(0.0, 0.0, 0.0);
	if (keycode == LEFT_ARROW)
	{
		adjust = vec3_sub(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
	}
	if (keycode == RIGHT_ARROW)
	{
		adjust = vec3_add(adjust, vec3_new(0.0, CAM_ROT_SPEED, 0.0));
	}
	if (keycode == UP_ARROW)
	{
		adjust = vec3_add(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
	}
	if (keycode == DOWN_ARROW)
	{
		adjust = vec3_sub(adjust, vec3_new(CAM_ROT_SPEED, 0.0, 0.0));
	}
//	adjust = deg2radvec(adjust);
	/* do angle shit */
	// printmatrix(my_mlx->cam->c2w);
	// printf("\n");
	// printvec(adjust, "adjust=");
	angles = mat4_angles(adjust);
	// printf("angles be:\n");
	// printmatrix(angles);
	// printf("\n");
	my_mlx->cam->v = pleurmatrix(my_mlx->cam->v, rotate(adjust));
	my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s, vec3_add(my_mlx->cam->s, my_mlx->cam->v));
//	my_mlx->cam->c2w = multmatrix(my_mlx->cam->c2w, angles);
	// printmatrix(my_mlx->cam->c2w);
	newframe(my_mlx);
}

int		keyinput(int keycode, t_data *my_mlx)
{
	wasd(keycode, my_mlx);
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
		printmatrix(my_mlx->cam->c2w);
		printf("\n");
		my_mlx->cam->c2w = multmatrix(my_mlx->cam->c2w, rotz(CAM_ROT_SPEED));
		printmatrix(my_mlx->cam->c2w);
		// my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s, vec3_add(my_mlx->cam->s, my_mlx->cam->v));
		newframe(my_mlx);
	}
	if (keycode == NUMZERO)
	{
		my_mlx->cam->c2w = multmatrix(my_mlx->cam->c2w, rotz(-CAM_ROT_SPEED));
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