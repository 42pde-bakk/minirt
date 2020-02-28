/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:01:34 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/28 16:23:44 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

void	hit(t_data *my_mlx, int x, int y)
{
	if (my_mlx->ray->length < __INT_MAX__)
		my_mlx->ray->colour = light_tracing(my_mlx);
	put_rgb(my_mlx, x, y, my_mlx->ray->colour);
	my_mlx->ray->length = __INT_MAX__;
	my_mlx->ray->colour = colour_new(0.0, 0.0, 0.0);
	my_mlx->ray->hitnormal = vec3_new(0.0, 0.0, 0.0);
}

void	*render_pixel(void *param)
{
	int		x;
	int		y;
	double	pndcy;
	double	pndcx;
	t_arg	*arg;

	arg = param;
	y = arg->threadnr;
	while (y < arg->my_mlx->scene->height)
	{
		x = 0;
		pndcy = ndcy(arg->my_mlx, y);
		while (x < arg->my_mlx->scene->width)
		{
			pndcx = ndcx(arg->my_mlx, x);
			// printf("xy=[%i, %i], pndcxy=[%f, %f]\n", x, y, pndcx, pndcy);
			setcamera(arg->my_mlx, pndcx, pndcy);
			find_objects(arg->my_mlx);
			hit(arg->my_mlx, x, y);
			x++;
		}
		y = y + THREADCOUNT;
	}
	// pthread_exit(NULL);
	return (NULL);
}

t_arg	*new_arg(t_data *my_mlx, int threadnr)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg)); //also needs to be freed
	new->my_mlx = my_mlx;
	new->threadnr = threadnr;
	return (new);
}

#if BONUS == 1

void	ray(t_data *my_mlx)
{
	pthread_t	threads[THREADCOUNT];
	t_arg		*arg[THREADCOUNT];
	int			i;

	i = 0;
	while (i < THREADCOUNT)
	{
		arg[i] = new_arg(my_mlx, i);
		if (pthread_create(&threads[i], NULL, render_pixel, arg[i]) != 0)
		{
			ft_putstr_fd("Error\nThread creation failed. Terminating\n", 2);
			freemachine(my_mlx);
		}
		printf("creating new thread:%d\n", i);
		i++;
	}
	i = 0;
	while (i < THREADCOUNT)
	{
		printf("joining old thread:%d\n", i);
		if (pthread_join(threads[i], NULL) != 0)
		{
			ft_putstr_fd("Error\nThread joining failed. Terminating\n", 2);
			freemachine(my_mlx);
		}
		i += 1;
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
			setcamera(my_mlx, pndcx, pndcy);
			find_objects(my_mlx);
			hit(my_mlx, x, y);
			x++;
		}
		y++;
		x = 0;
	}
}

#endif
