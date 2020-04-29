/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:30:15 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:30:16 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

void	hit(t_data *my_mlx, int x, int y, int threadnr)
{
	if (my_mlx->ray[threadnr]->length < __INT_MAX__)
		my_mlx->ray[threadnr]->colour = light_tracing(my_mlx, threadnr);
	put_rgb(my_mlx, x, y, my_mlx->ray[threadnr]->colour);
	my_mlx->ray[threadnr]->length = __INT_MAX__;
	my_mlx->ray[threadnr]->colour = colour_new(0.0, 0.0, 0.0);
	my_mlx->ray[threadnr]->hitnormal = vec3_new(0.0, 0.0, 0.0);
}

t_arg	*new_arg(t_data *my_mlx, int threadnr)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		exit(ft_putstr_int("Error\nMalloc for argstruct failed\n", 2));
	new->my_mlx = my_mlx;
	new->threadnr = threadnr;
	return (new);
}

void	threading(t_data *my_mlx)
{
	pthread_t	threads[THREADCOUNT];
	t_arg		*arg[THREADCOUNT];
	int			i;

	i = 0;
	while (i < THREADCOUNT)
	{
		arg[i] = new_arg(my_mlx, i);
		if (pthread_create(&threads[i], NULL, render_pixel, arg[i]) != 0)
			exit_putstr(my_mlx, "Error\nThread creation failed.\n", 2);
		i++;
	}
	i = 0;
	while (i < THREADCOUNT)
	{
		if (pthread_join(threads[i], NULL) != 0)
			exit_putstr(my_mlx, "Error\nThread joining failed.\n", 2);
		i++;
	}
	i = 0;
	while (i < THREADCOUNT)
	{
		free(arg[i]);
		i++;
	}
}

#if BONUS == 1

void	ray(t_data *my_mlx)
{
	double	distance;

	distance = 1;
	if (STEREOSCOPY == 1)
	{
		my_mlx->cam->s.x -= distance;
		my_mlx->bonus->stereoscopy = 1;
		threading(my_mlx);
		my_mlx->cam->s.x += 2 * distance;
		my_mlx->bonus->stereoscopy = 2;
		threading(my_mlx);
		my_mlx->cam->s.x += distance;
	}
	else
	{
		threading(my_mlx);
	}
}

#else

void	ray(t_data *my_mlx)
{
	int		x;
	int		y;
	double	pndcy;
	double	pndcx;

	x = 0;
	y = 0;
	while (y < my_mlx->scene->height)
	{
		pndcy = ndcy(my_mlx, y);
		while (x < my_mlx->scene->width)
		{
			pndcx = ndcx(my_mlx, x);
			my_mlx->ray[0]->v = setcamera(my_mlx, pndcx, pndcy);
			find_objects(my_mlx, 0);
			hit(my_mlx, x, y, 0);
			x++;
		}
		y++;
		x = 0;
	}
}

#endif
