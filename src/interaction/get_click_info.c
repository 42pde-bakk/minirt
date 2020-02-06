/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_click_info.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 18:44:55 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/06 21:31:02 by Peer de Bak   ########   odam.nl         */
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

int		object_edit_properties(t_data *my_mlx, double distancex,
		double distancey)
{
	if (my_mlx->click->identifier == 's')
		sphere_edit_properties(my_mlx, distancex, distancey);
	else if (my_mlx->click->identifier == 't')
		triangle_edit_properties(my_mlx, distancex, distancey);
	else if (my_mlx->click->identifier == 'q')
		square_edit_properties(my_mlx, distancex, distancey);
	else if (my_mlx->click->identifier == 'c')
		cylinder_edit_properties(my_mlx, distancex, distancey);
	else if (my_mlx->click->identifier == 'p')
		plane_edit_properties(my_mlx, distancex, distancey);
	return (1);
}

void	clean_click_info(t_data *my_mlx)
{
	my_mlx->click->identifier = '0';
	my_mlx->click->index = -1;
	my_mlx->click->pos = vec3_new(0.0, 0.0, 0.0);
	my_mlx->click->distance = 0.0;
	my_mlx->click->x = 0;
	my_mlx->click->y = 0;
}

void	get_click_info(int x, int y, t_data *my_mlx)
{
	t_vec3	ray;
	int		distancex;
	int		distancey;

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
		distancex = (x - my_mlx->click->x);
		distancey = (y - my_mlx->click->y);
		object_edit_properties(my_mlx, distancex, distancey);
		my_mlx->click->state = 0;
		newframe(my_mlx);
	}
}
