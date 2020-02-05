/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 23:51:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/04 21:25:11 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		click_object(t_data *my_mlx, t_vec3 ray)
{
	t_square	*tmpsquare;
	t_triangle	*tmptriangle;
	t_sphere	*tmpsphere;
	t_cylinder	*tmpcylinder;
	t_plane		*tmpplane;
	double		distance;
	double		ret;
	int			i;

	tmpsquare = my_mlx->square;
	tmptriangle = my_mlx->triangle;
	tmpsphere = my_mlx->sphere;
	tmpcylinder = my_mlx->cylinder;
	tmpplane = my_mlx->plane;
	distance = __INT_MAX__;
	i = 0;
	while (tmpsphere)
	{
		ret = click_sphere(tmpsphere, my_mlx, ray);
		if (ret < distance && ret >= 0.0)
		{
			distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "sphere";
			my_mlx->click->identifier = 's';
		}
		i++;
		tmpsphere = tmpsphere->next;
	}
	i = 0;
	while (tmptriangle)
	{
		ret = click_triangle(tmptriangle, my_mlx, ray);
		if (ret < distance && ret >= 0.0)
		{
			distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "triangle";
			my_mlx->click->identifier = 't';
		}
		i++;
		tmptriangle = tmptriangle->next;
	}
	i = 0;
	while (tmpsquare)
	{
		ret = click_square(tmpsquare, my_mlx, ray);
		if (ret < distance && ret >= 0.0)
		{
			distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "square";
			my_mlx->click->identifier = 'q';
		}
		i++;
		tmpsquare = tmpsquare->next;
	}
	i = 0;
	while (tmpcylinder)
	{
		ret = click_cylinder(tmpcylinder, my_mlx, ray);
		if (ret < distance && ret >= 0.0)
		{
			distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "cylinder";
			my_mlx->click->identifier = 'c';
		}
		i++;
		tmpcylinder = tmpcylinder->next;
	}
	return (1);
}