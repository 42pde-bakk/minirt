/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readinput.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:22:37 by peer          #+#    #+#                 */
/*   Updated: 2020/05/04 22:38:35 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (my_mlx->click->state == 0)
		arrowkeys(keycode, my_mlx);
	else
		object_change_rotsize(keycode, my_mlx);
	swapcameras(keycode, my_mlx);
	if (keycode == ESCAPE)
		freemachine(my_mlx);
	return (1);
}
