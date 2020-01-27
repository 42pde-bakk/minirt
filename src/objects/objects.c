/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:08:17 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		visualize_lightsource(t_data *my_mlx)
{
	t_vec3	tmp;
	double	t;
	double	x;
	double	y;
	double	t1;
	double	t2;
	t_vec3	p;

	tmp = vec3_sub(my_mlx->light->s, my_mlx->cam->s);
	t = dotproduct(tmp, my_mlx->ray->v);
	if (t < 0)
		return (0);
	p = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, t));
	y = find_length(p, my_mlx->light->s);
	if (y < 1)
	{
		if (pow(2, 2) - (y * y) < 0)
			return (0);
		x = sqrt(pow(1, 2) - pow(y, 2));
		t1 = (t - x);
		t2 = t + x;
		if (t1 < my_mlx->ray->length || my_mlx->ray->length == 0)
		{
			if (my_mlx->cam->s.z > t1 * my_mlx->ray->v.z)
				my_mlx->ray->length = t2;
			else
				my_mlx->ray->length = t1;
			my_mlx->ray->colour = my_mlx->light->colour;
			// my_mlx->ray->hitnormal = vec3_sub(my_mlx->sphere->s, vec3_mult(my_mlx->ray->v, t1));
			// my_mlx->ray->hitnormal = vec3_normalize(my_mlx->ray->hitnormal);
		}
		return (1);
	}
	return (0);	
}

int		find_objects(t_data *my_mlx)
{
	t_sphere	*head;
	t_plane		*phead;
	t_triangle	*thead;
	t_square	*shead;
	t_light		*lighthead;
	int			ret;

	lighthead = my_mlx->light;
	while (my_mlx->light)
	{
		ret = visualize_lightsource(my_mlx);
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = lighthead;
	
	phead = my_mlx->plane;
	while (my_mlx->plane)
	{
		ret = find_plane(my_mlx);
		my_mlx->plane = my_mlx->plane->next;
	}
	my_mlx->plane = phead;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
		ret = find_sphere(my_mlx);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;

	thead = my_mlx->triangle;
	while (my_mlx->triangle)
	{
		ret = find_triangle(my_mlx->triangle, my_mlx);
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle = thead;

	shead = my_mlx->square;
	while (my_mlx->square)
	{
		ret = find_square(my_mlx);
		my_mlx->square = my_mlx->square->next;
	}
	my_mlx->square = shead;
	return (ret);
}
