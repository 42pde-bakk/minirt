/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freebwilbers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 22:29:02 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/05/04 22:38:53 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	freeplane(void *in)
{
	t_plane *tmp;
	t_plane *plane;

	plane = (t_plane*)in;
	while (plane)
	{
		tmp = plane->next;
		free(plane);
		plane = tmp;
	}
}

void	freerays(t_data *my_mlx)
{
	int	i;

	i = 0;
	while (i < THREADCOUNT)
	{
		free(my_mlx->ray[i]);
		i++;
	}
}

int		freemachine(t_data *my_mlx)
{
	static int	check = 0;

	if (check > 0)
		return (0);
	check++;
	close(my_mlx->fd);
	freeplane(my_mlx->plane);
	freeplane(my_mlx->sphere);
	freeplane(my_mlx->square);
	freeplane(my_mlx->triangle);
	freeplane(my_mlx->cylinder);
	freeplane(my_mlx->light);
	free(my_mlx->scene);
	freerays(my_mlx);
	free(my_mlx->click);
	if (my_mlx->mlx_img != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img);
	if (my_mlx->mlx_img2 != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img2);
	if (my_mlx->win_ptr != NULL)
		mlx_destroy_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
	if (BONUS == 1 && my_mlx->bonus->uvimg != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->bonus->uvimg);
	exit(ft_putstr_int("Hope you had fun miniRT-ing!\nSee you next time\n", 1));
}

int		exit_putstr(t_data *my_mlx, char *s, int fd)
{
	static int	check = 0;

	if (check > 0)
		return (0);
	check++;
	ft_putstr_fd(s, fd);
	close(my_mlx->fd);
	freeplane(my_mlx->plane);
	freeplane(my_mlx->sphere);
	freeplane(my_mlx->square);
	freeplane(my_mlx->triangle);
	freeplane(my_mlx->cylinder);
	freeplane(my_mlx->light);
	free(my_mlx->scene);
	freerays(my_mlx);
	free(my_mlx->click);
	if (my_mlx->mlx_img != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img);
	if (my_mlx->mlx_img2 != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img2);
	if (my_mlx->win_ptr != NULL)
		mlx_destroy_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
	if (my_mlx->bonus->uvimg != NULL)
		mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->bonus->uvimg);
	exit(ft_putstr_int("Hope you had fun miniRT-ing!\nSee you next time\n", 1));
}
