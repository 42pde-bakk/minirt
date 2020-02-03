/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/04 00:26:08 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	wasd(int keycode, t_data *my_mlx)
{
	t_vec3	movement;

	movement = vec3_new(0.0, 0.0, 0.0);
	if ((keycode >= AKEY && keycode <= DKEY) || (keycode >= QKEY && keycode <= EKEY))
	{
		// printmatrix(my_mlx->cam->c2w);
		// printf("\n");
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

t_vec3	lookingdir(t_data *my_mlx, double x, double y)
{
	t_vec3	out;

	out = vec3_new(-x, y, -1.0);
	out = vec3_normalize(out);
	out = pleurmatrix(out, my_mlx->cam->c2w);
	out = vec3_normalize(out);
	return (out);
}

int		mouseinput(int button, int x, int y, t_data *my_mlx)
{
	t_vec3	ray;
	char	*object;
	int		index;

	if (button == 1)
	{
		object = "object";
		index = -1;
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		printf("x=%d, y=%d\n", x, y);
		ray = lookingdir(my_mlx, ndcx(my_mlx, x), ndcy(my_mlx, y));
		printvec(ray, "lookingdir");
		click_object(my_mlx, &object, &index, ray);
		printf("obj=%s, index=%i\n", object, index);
	}
	return (1);
}
