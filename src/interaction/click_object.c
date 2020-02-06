/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 23:51:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/06 21:18:28 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	click_object_triangle(t_data *my_mlx, t_vec3 ray)
{
	t_triangle	*tmptriangle;
	int			i;
	double		ret;
	double		ret2;
	t_triangle	rev;

	i = 0;
	tmptriangle = my_mlx->triangle;
	while (tmptriangle)
	{
		ret = click_triangle(tmptriangle, my_mlx, ray);
		rev = tri_rev(*tmptriangle);
		ret2 = click_triangle(&rev, my_mlx, ray);
		if (ret2 >= 0.0 && (ret2 < ret || ret < 0.0))
			ret = ret2;
		if (ret < my_mlx->click->distance && ret >= 0.0)
		{
			my_mlx->click->distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "triangle";
			my_mlx->click->identifier = 't';
		}
		i++;
		tmptriangle = tmptriangle->next;
	}
}

int		click_object_square(t_data *my_mlx, t_vec3 ray)
{
	t_square	*tmpsquare;
	int			i;
	double		ret;

	i = 0;
	tmpsquare = my_mlx->square;
	while (tmpsquare)
	{
		ret = click_square(tmpsquare, my_mlx, ray);
		if (ret < my_mlx->click->distance && ret >= 0.0)
		{
			my_mlx->click->distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "square";
			my_mlx->click->identifier = 'q';
		}
		i++;
		tmpsquare = tmpsquare->next;
	}
	return (1);
}

int		click_object_sphere(t_data *my_mlx, t_vec3 ray)
{
	t_sphere	*tmpsphere;
	int			i;
	double		ret;

	i = 0;
	tmpsphere = my_mlx->sphere;
	while (tmpsphere)
	{
		ret = click_sphere(tmpsphere, my_mlx, ray);
		if (ret < my_mlx->click->distance && ret >= 0.0)
		{
			my_mlx->click->distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "sphere";
			my_mlx->click->identifier = 's';
		}
		i++;
		tmpsphere = tmpsphere->next;
	}
	return (1);
}

int		click_object_cylinder(t_data *my_mlx, t_vec3 ray)
{
	t_cylinder	*tmpcylinder;
	double		ret;
	int			i;

	tmpcylinder = my_mlx->cylinder;
	i = 0;
	while (tmpcylinder)
	{
		ret = click_cylinder(tmpcylinder, my_mlx, ray);
		if (ret < my_mlx->click->distance && ret >= 0.0)
		{
			my_mlx->click->distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "cylinder";
			my_mlx->click->identifier = 'c';
		}
		i++;
		tmpcylinder = tmpcylinder->next;
	}
	return (1);
}

int		click_object_plane(t_data *my_mlx, t_vec3 ray)
{
	t_plane	*tmpplane;
	double	ret;
	int		i;

	tmpplane = my_mlx->plane;
	i = 0;
	while (tmpplane)
	{
		ret = click_plane(tmpplane, my_mlx, ray);
		if (ret < my_mlx->click->distance && ret >= 0.0)
		{
			my_mlx->click->distance = ret;
			my_mlx->click->index = i;
			my_mlx->click->object = "plane";
			my_mlx->click->identifier = 'p';
		}
		i++;
		tmpplane = tmpplane->next;
	}
	return (1);
}

int		click_object(t_data *my_mlx, t_vec3 ray)
{
	int	i;

	my_mlx->click->distance = __INT_MAX__;
	i = 0;
	click_object_cylinder(my_mlx, ray);
	click_object_sphere(my_mlx, ray);
	click_object_triangle(my_mlx, ray);
	click_object_square(my_mlx, ray);
	click_object_plane(my_mlx, ray);
	if (my_mlx->click->index >= 0)
	{
		my_mlx->click->state = 1;
		mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr,
		0, my_mlx->scene->height - 10, 0xFFFFFF, my_mlx->click->object);
	}
	return (1);
}
