/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/14 17:20:34 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			find_obstacles(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_sphere	*head;
	int			ret;

	ret =  0;
	head = my_mlx->sphere;
	while (my_mlx->sphere && ret == 0)
	{
		ret = sphere_obs(my_mlx, pos, dir);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;

	return (ret);
}

t_col	ambient_lighting(t_data *my_mlx, t_col colour)
{
	t_col		ambient;
	
	ambient.r = my_mlx->scene->amblightcolour.r;
	ambient.g = my_mlx->scene->amblightcolour.g;
	ambient.b = my_mlx->scene->amblightcolour.b;
	colour.r *= ((double)ambient.r / 255);
	colour.r *= my_mlx->scene->ambintensity;
	colour.g *= ((double)ambient.g / 255);
	colour.g *= my_mlx->scene->ambintensity;
	colour.b *= ((double)ambient.b / 255);
	colour.b *= my_mlx->scene->ambintensity;
	return (colour);;
}

t_col		light_add(t_data *my_mlx, t_col light, t_vec3 dir, int ret)
{
	t_col	hitcol;
	t_col	lightcol;
	double	intensity;

	lightcol = my_mlx->light->colour;
	hitcol = my_mlx->ray->colour;
	if (ret == 1)
	{	
		intensity = fmin(my_mlx->light->brightness / (4.0 * M_PI *vec3_sqr(dir))
		* fmax(dotproduct(my_mlx->ray->hitnormal, dir), 0.0f) * 0.2, 1.0f);
	hitcol = colour_mult(hitcol, intensity, lightcol);
	}
	else
		hitcol = colour_new();

//	create new colour,
//	mult hitcolor with light
//	add new and hit*light
//	repeat last 2 steps for each light;
	return (colour_add(light, hitcol));
}

t_col	light_tracing(t_data *my_mlx, t_col hitcol)
{
	t_vec3	pos;
	t_vec3	dir;
	t_light	*head;
	t_col	light;
	int		ret;

	ret = 0;
	head = my_mlx->light;
	light = colour_new();
	while (my_mlx->light)
	{
		pos = vec_mult(my_mlx->ray->v, my_mlx->ray->length);
		dir = vector_sub(my_mlx->light->s, pos);
		ret = find_obstacles(my_mlx, pos, dir);
		light = light_add(my_mlx, light, dir, ret);
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = head;
	light = ambient_lighting(my_mlx, light);
	return (hitcol);
}