/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/27 14:43:33 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col		light_add(t_data *my_mlx, int ret)
{
	t_col	hitcol;
	double	intensity;
	t_light	light;
	t_vec3	pos;
	t_vec3	dir;
	double	tmp;

	// pos = vec3_sub(pos, vec3_mult(dir, EPSILON));
	light = *my_mlx->light;
	hitcol = my_mlx->ray->colour;
	if (ret == 0)
	{
		pos = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, my_mlx->ray->length - EPSILON));
		dir = vec3_sub(my_mlx->light->s, pos);
		double r2 = vec3_sqr(dir);
		dir = vec3_normalize(dir);
		tmp = fmax(dotproduct(my_mlx->ray->hitnormal, dir), 0.0);
		intensity = fmin((10.0 * ALBEDO * light.brightness * 1) / (4.0 * M_PI * r2), 1.0);
		return (colour_mul(hitcol, light.colour, intensity));
	}
	else
		return (colour_new(0, 0, 0));
}

t_col	light_tracing(t_data *my_mlx)
{
	t_light	*head;
	t_col	colour;
	int		ret;
	double	lightdistance;

	ret = 0;
	head = my_mlx->light;
	colour = colour_mul(my_mlx->ray->colour, my_mlx->scene->amblightcolour, my_mlx->scene->ambintensity);
	while (my_mlx->light)
	{
		lightdistance = find_length(vec3_mult(my_mlx->ray->v, my_mlx->ray->length - EPSILON), my_mlx->light->s);
		ret = find_obstacles(my_mlx, lightdistance);
		colour = colour_add(colour, light_add(my_mlx, ret));
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = head;
	if (my_mlx->ray->colour.r == 255 && my_mlx->ray->colour.g == 255 && my_mlx->ray->colour.b == 255)
		colour = colour_new(255, 255, 255);
	colour = colour_cap(colour);
	return (colour);
}