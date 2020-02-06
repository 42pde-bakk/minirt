/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 20:28:54 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/06 01:35:14 by Peer de Bak   ########   odam.nl         */
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
		my_mlx->click->state = 0;
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
		my_mlx->click->state = 0;
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
		my_mlx->click->state = 0;
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

int		object_edit_properties(t_data *my_mlx, double distancex, double distancey)
{
	if (my_mlx->click->identifier == 's')
		sphere_edit_properties(my_mlx, distancex, distancey);
	else if (my_mlx->click->identifier == 't')
		triangle_edit_properties(my_mlx, distancex, distancey);
	// else if (my_mlx->click->identifier == 'q')
	// 	square_edit_properties(my_mlx, distancex, distancey);
	// else if (my_mlx->click->identifier == 'c')
	// 	cylinder_edit_properties(my_mlx, distancex, distancey);
	// else if (my_mlx->click->identifier == 'p')
	// 	plane_edit_properties(my_mlx, distancex, distancey);
	return (1);
}

int		mouseinput(int button, int x, int y, t_data *my_mlx)
{
	t_vec3		ray;
	double		distancex;
	double		distancey;

	if (button == 1 && my_mlx->click->state == 0)
	{
		my_mlx->click->identifier = '0';
		my_mlx->click->index = -1;
		my_mlx->click->pos = vec3_new(0.0, 0.0, 0.0);
		my_mlx->click->distance = 0.0;
		my_mlx->click->x = 0;
		my_mlx->click->y = 0;
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		y -= 21;
		my_mlx->click->x = x;
		my_mlx->click->y = y;
		printf("x=%d, y=%d\n", x, y);
		ray = lookingdir(my_mlx, ndcx(my_mlx, x), ndcy(my_mlx, y));
//		printvec(ray, "lookingdir");
		click_object(my_mlx, ray);
		printf("obj=%c, index=%i\n", my_mlx->click->identifier, my_mlx->click->index);
		printvec(my_mlx->click->pos, "object position");
		if (my_mlx->click->index != -1)
			my_mlx->click->state = 1;
	}
	else if (button == 1 && my_mlx->click->state == 1)
	{
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		y -= 21;
		distancex = (x - my_mlx->click->x);
		distancey = (y - my_mlx->click->y);
		printf("distancex = %f, distancey = %f\n", distancex, distancey);
		object_edit_properties(my_mlx, distancex, distancey);
		my_mlx->click->state = 0;
		my_mlx->click->index = -1;
		newframe(my_mlx);
	}
	return (1);
}
