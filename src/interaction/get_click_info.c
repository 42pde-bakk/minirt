/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_click_info.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:22:50 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:22:51 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	lookingdir(t_data *my_mlx, double x, double y)
{
	t_vec3	out;

	out = vec3_new(-x, y, -1.0);
	out = vec3_normalize(out);
	out = pleurmatrix(out, my_mlx->cam->c2w);
	out = vec3_normalize(out);
	return (out);
}

void	clean_click_info(t_data *my_mlx)
{
	my_mlx->click->identifier = '0';
	my_mlx->click->index = -1;
	my_mlx->click->pos = vec3_new(0.0, 0.0, 0.0);
	my_mlx->click->distance = 0.0;
	my_mlx->click->dist_r = 0.0;
	my_mlx->click->dist_up = 0.0;
	my_mlx->click->dist_fw = 0.0;
	my_mlx->click->x = 0;
	my_mlx->click->y = 0;
	my_mlx->click->sizemult = 1.0;
	my_mlx->click->heightmult = 1.0;
	my_mlx->click->rotation = vec3_new(0.0, 0.0, 0.0);
	my_mlx->click->mousemovestate = 0;
}

void	get_click_info(int x, int y, t_data *my_mlx)
{
	t_vec3	ray;

	if (my_mlx->click->state == 0)
	{
		clean_click_info(my_mlx);
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		y -= 21;
		my_mlx->click->x = x;
		my_mlx->click->y = y;
		ray = lookingdir(my_mlx, ndcx(my_mlx, x), ndcy(my_mlx, y));
		click_object(my_mlx, ray);
	}
	else
	{
		mlx_mouse_get_pos(my_mlx->win_ptr, &x, &y);
		y -= 21;
		my_mlx->click->dist_r = (x - my_mlx->click->x);
		my_mlx->click->dist_up = (y - my_mlx->click->y);
		object_edit_properties(my_mlx);
		my_mlx->click->state = 0;
		newframe(my_mlx);
	}
}
