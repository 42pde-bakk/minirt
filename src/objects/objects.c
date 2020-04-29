/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:40 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:14:41 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		loop_cylinders_spheres(t_data *my_mlx, int threadnr)
{
	t_cylinder	*tmpcylinder;
	t_sphere	*tmpsphere;
	int			ret;

	ret = 0;
	tmpcylinder = my_mlx->cylinder;
	while (tmpcylinder)
	{
		ret = find_cylinder(tmpcylinder, my_mlx, threadnr);
		tmpcylinder = tmpcylinder->next;
	}
	tmpsphere = my_mlx->sphere;
	while (tmpsphere)
	{
		ret = find_sphere(tmpsphere, my_mlx, threadnr);
		tmpsphere = tmpsphere->next;
	}
	return (ret);
}

int		find_objects(t_data *my_mlx, int threadnr)
{
	t_plane		*tmpplane;
	t_triangle	*tmptriangle;
	t_square	*tmpsquare;
	int			ret;

	tmpplane = my_mlx->plane;
	while (tmpplane)
	{
		ret = find_plane(tmpplane, my_mlx, threadnr);
		tmpplane = tmpplane->next;
	}
	ret = loop_cylinders_spheres(my_mlx, threadnr);
	tmptriangle = my_mlx->triangle;
	while (tmptriangle)
	{
		ret = find_triangle(tmptriangle, my_mlx, threadnr);
		tmptriangle = tmptriangle->next;
	}
	tmpsquare = my_mlx->square;
	while (tmpsquare)
	{
		ret = find_square(tmpsquare, my_mlx, threadnr);
		tmpsquare = tmpsquare->next;
	}
	return (ret);
}
