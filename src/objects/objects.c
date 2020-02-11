/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 16:09:13 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		loop_cylinders_spheres(t_data *my_mlx)
{
	t_cylinder	*tmpcylinder;
	t_sphere	*tmpsphere;
	int			ret;

	ret = 0;
	tmpcylinder = my_mlx->cylinder;
	while (tmpcylinder)
	{
		ret = find_cylinder(tmpcylinder, my_mlx);
		tmpcylinder = tmpcylinder->next;
	}
	tmpsphere = my_mlx->sphere;
	while (tmpsphere)
	{
		ret = find_sphere(tmpsphere, my_mlx);
		tmpsphere = tmpsphere->next;
	}
	return (ret);
}

int		find_objects(t_data *my_mlx)
{
	t_plane		*tmpplane;
	t_triangle	*tmptriangle;
	t_square	*tmpsquare;
	int			ret;

	tmpplane = my_mlx->plane;
	while (tmpplane)
	{
		ret = find_plane(tmpplane, my_mlx);
		tmpplane = tmpplane->next;
	}
	ret = loop_cylinders_spheres(my_mlx);
	tmptriangle = my_mlx->triangle;
	while (tmptriangle)
	{
		ret = find_triangle(tmptriangle, my_mlx);
		tmptriangle = tmptriangle->next;
	}
	tmpsquare = my_mlx->square;
	while (tmpsquare)
	{
		ret = find_square(tmpsquare, my_mlx);
		tmpsquare = tmpsquare->next;
	}
	return (ret);
}
