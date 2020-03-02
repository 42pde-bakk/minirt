/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_properties.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 01:29:43 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/01 18:43:08 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	obj_move(t_vec3 pos, t_data *my_mlx)
{
	t_vec3	mult_r;
	t_vec3	mult_up;
	t_vec3	mult_fw;

	mult_r = vec3_mult(my_mlx->cam->c2w.r, my_mlx->click->dist_r *
	my_mlx->click->distance
	/ my_mlx->scene->width);
	mult_up = vec3_mult(my_mlx->cam->c2w.up, my_mlx->click->dist_up *
	my_mlx->click->distance
	/ my_mlx->scene->height);
	mult_fw = vec3_mult(my_mlx->cam->c2w.fw, my_mlx->click->dist_fw);
	pos = vec3_sub(pos, mult_r);
	pos = vec3_sub(pos, mult_up);
	pos = vec3_sub(pos, mult_fw);
	return (pos);
}

int		object_edit_properties(t_data *my_mlx)
{
	if (my_mlx->click->identifier == 's')
		sphere_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 't')
		triangle_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'q')
		square_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'c')
		cylinder_edit_properties(my_mlx);
	else if (my_mlx->click->identifier == 'p')
		plane_edit_properties(my_mlx);
	return (1);
}

void	object_sizemult(int keycode, t_data *my_mlx)
{
	if (keycode == NUMPLUS)
		my_mlx->click->sizemult *= 1.2;
	if (keycode == NUMMINUS)
		my_mlx->click->sizemult /= 1.2;
	if (keycode == NUMSLASH)
		my_mlx->click->heightmult /= 1.2;
	if (keycode == NUMSTAR)
		my_mlx->click->heightmult *= 1.2;
}

void	object_change_rotsize(int keycode, t_data *my_mlx)
{
	t_vec3	angle;

	object_sizemult(keycode, my_mlx);
	angle = vec3_new(0.0, 0.0, 0.0);
	if (keycode >= NUMTWO && keycode <= NUMNINE)
	{
		if (keycode == NUMFOUR)
			angle = vec3_sub(angle, vec3_new(0.0, 3 * CAM_ROT_SPEED, 0.0));
		if (keycode == NUMSIX)
			angle = vec3_add(angle, vec3_new(0.0, 3 * CAM_ROT_SPEED, 0.0));
		if (keycode == NUMTWO)
			angle = vec3_sub(angle, vec3_new(3 * CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMEIGHT)
			angle = vec3_add(angle, vec3_new(3 * CAM_ROT_SPEED, 0.0, 0.0));
		if (keycode == NUMSEVEN)
			angle = vec3_sub(angle, vec3_new(0.0, 0.0, 3 * CAM_ROT_SPEED));
		if (keycode == NUMNINE)
			angle = vec3_add(angle, vec3_new(0.0, 0.0, 3 * CAM_ROT_SPEED));
		my_mlx->click->rotation = addrotation(my_mlx->click->rotation, angle);
		object_edit_properties(my_mlx);
	}
}

#if BONUS == 1

int		mouseinput(int button, int x, int y, t_data *my_mlx)
{
	if (my_mlx->click->state == 0)
	{
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		my_mlx->click->dist_r = x - my_mlx->click->x;
		my_mlx->click->dist_up = y - my_mlx->click->y;
		my_mlx->cam->v = addrotation(my_mlx->cam->v, vec3_new(my_mlx->click->dist_up, my_mlx->click->dist_r, 0.0));
		my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s, vec3_add(my_mlx->cam->s, my_mlx->cam->v));
		my_mlx->click->x = x;
		my_mlx->click->y = y;
		newframe(my_mlx);
	}
	if (my_mlx->click->state == 1 && (button == 4 || button == 5))
	{
		if (button == 4)
			my_mlx->click->dist_fw += 10;
		else if (button == 5)
			my_mlx->click->dist_fw -= 10;
	}
	if (button == 1)
		get_click_info(x, y, my_mlx);
	return (1);
}

#else

int		mouseinput(int button, int x, int y, t_data *my_mlx)
{
	if (my_mlx->click->state == 1 && (button == 4 || button == 5))
	{
		if (button == 4)
			my_mlx->click->dist_fw += 10;
		else if (button == 5)
			my_mlx->click->dist_fw -= 10;
	}
	if (button == 1)
		get_click_info(x, y, my_mlx);
	return (1);
}

#endif
