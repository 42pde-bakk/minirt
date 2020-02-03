/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 23:51:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/04 00:25:38 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	click_sphere(t_sphere *sp, t_data *my_mlx, t_vec3 ray)
{
	double	t0;
	t_vec3	p;
	double	y;

	t0 = dotproduct(vec3_sub(sp->s, my_mlx->cam->s), ray);
	if (t0 < 0)
		return (-1);
	p = vec3_add(my_mlx->cam->s, vec3_mult(ray, t0));
	y = find_length(p, sp->s);
	if (y > sp->diameter / 2 || y < 0 || pow(sp->diameter / 2, 2) - y * y < 0)
		return (-1);
	return (t0 - sqrt(pow(sp->diameter / 2, 2) - pow(y, 2)));	
}

int		click_object(t_data *my_mlx, char **object, int *index, t_vec3 ray)
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
		if (ret < distance && ret >= 0)
		{
			distance = ret;
			*index = i;
			*object = "sphere";
		}
		i++;
		tmpsphere = tmpsphere->next;
	}
	return (1);
}