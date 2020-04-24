/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouseinput.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:26:38 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 16:24:46 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	do_rotate(t_data *my_mlx, t_vec3 adjust, int x, int y)
{
	mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
	my_mlx->click->dist_r = (x - my_mlx->click->x) / my_mlx->scene->width;
	my_mlx->click->dist_r = (y - my_mlx->click->y) / my_mlx->scene->height;
	adjust.y = (x - my_mlx->click->x) / my_mlx->scene->width * 10;
	adjust.x = (y - my_mlx->click->y) / my_mlx->scene->height * 10;
	my_mlx->click->state = 0;
	my_mlx->cam->v = addrotation(my_mlx->cam->v, adjust);
	my_mlx->cam->c2w = mat4_lookat(my_mlx->cam->s,
	vec3_add(my_mlx->cam->s, my_mlx->cam->v));
	newframe(my_mlx);
}

#if BONUS == 1 && MOUSEROTATE == 1

int		mouseinput(int button, int x, int y, t_data *my_mlx)
{
	t_vec3	adjust;

	adjust = vec3_new(0, 0, 0);
	(void)button;
	if (my_mlx->click->state == 0)
	{
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		y -= 21;
		my_mlx->click->x = x;
		my_mlx->click->y = y;
		my_mlx->click->state = 1;
	}
	else
	{
		do_rotate(my_mlx, adjust, x, y);
	}
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
