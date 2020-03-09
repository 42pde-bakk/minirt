/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 17:30:50 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/05 18:52:19 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#if BONUS == 1 && ANTIALIASING == 1

int		parse_resolution(t_data *my_mlx, char *line, int *i)
{
	static int	check = 0;
	int			max_resx;
	int			max_resy;

	if (check > 0)
		return (-1);
	check++;
	if (my_mlx->bmp == 1)
	{
		mlx_get_screen_size(my_mlx->mlx_ptr, &max_resx, &max_resy);
		my_mlx->scene->width = fmin(max_resx, ft_atof_peer(line, i));
		my_mlx->scene->height = fmin(max_resy, ft_atof_peer(line, i));
	}
	else
	{
		my_mlx->scene->width = ft_atof_peer(line, i);
		my_mlx->scene->height = ft_atof_peer(line, i);
	}
	my_mlx->scene->aawidth = 2 * my_mlx->scene->width;
	my_mlx->scene->aaheight = 2 * my_mlx->scene->height;
	if (my_mlx->scene->width <= 0.0 || my_mlx->scene->height <= 0.0)
		return (-1);
	return (1);
}

#else

int		parse_resolution(t_data *my_mlx, char *line, int *i)
{
	static int	check = 0;
	int			max_resx;
	int			max_resy;

	if (check > 0)
		return (-1);
	check++;
	if (my_mlx->bmp == 1)
	{
		mlx_get_screen_size(my_mlx->mlx_ptr, &max_resx, &max_resy);
		my_mlx->scene->width = fmin(max_resx, ft_atof_peer(line, i));
		my_mlx->scene->height = fmin(max_resy, ft_atof_peer(line, i));
	}
	else
	{
		my_mlx->scene->width = ft_atof_peer(line, i);
		my_mlx->scene->height = ft_atof_peer(line, i);
	}
	if (my_mlx->scene->width <= 0.0 || my_mlx->scene->height <= 0.0)
		return (-1);
	return (1);
}

#endif
