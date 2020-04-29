/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:22:28 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:22:29 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_object_triangle(t_data *my_mlx, t_vec3 ray)
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

int		get_object_square(t_data *my_mlx, t_vec3 ray)
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
			my_mlx->click->rotation = tmpsquare->normal;
		}
		i++;
		tmpsquare = tmpsquare->next;
	}
	return (1);
}

int		get_object_sphere(t_data *my_mlx, t_vec3 ray)
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

int		click_object(t_data *my_mlx, t_vec3 ray)
{
	int	i;

	my_mlx->click->distance = __INT_MAX__;
	i = 0;
	get_object_cylinder(my_mlx, ray);
	get_object_sphere(my_mlx, ray);
	get_object_triangle(my_mlx, ray);
	get_object_square(my_mlx, ray);
	get_object_plane(my_mlx, ray);
	if (my_mlx->click->index >= 0)
	{
		my_mlx->click->state = 1;
		mlx_string_put(my_mlx->mlx_ptr, my_mlx->win_ptr,
		0, my_mlx->scene->height - 10, WHITE, my_mlx->click->object);
	}
	return (1);
}
