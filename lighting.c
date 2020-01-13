/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/13 19:27:54 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned			colourremap01(t_data *my_mlx, double ret)
{
	int				r;
	int				g;
	int				b;
	unsigned		col;

	col = my_mlx->ray->colour;
	r = (col >> 16 & 0xff);
	g = (col >> 8 & 0xff);
	b = (col & 0xff);
//printf("remap: {%i, %i, %i} ret=%f\n", r, g, b, ret);
	r *= ret;
	g *= ret;
	b *= ret;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

// t_vec3	colour_mult(t_vec3 vec, double ret)
// {
// 	vec.x *= ret;
// 	rgb.y *= ret;
// 	rgb.z *= ret;
// 	return (rgb);
// }

int		plane_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	double	a;
	double	denom;
	double	t;

	tmp = vector_sub(my_mlx->plane->s, pos);
	denom = dotproduct(my_mlx->plane->normal, dir);
	if (denom > 0.000001)
	{
		a = dotproduct(tmp, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0)
			return (1);
	}
	return (0);
}

int		sphere_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	t_vec3	p;
	double	t;
	double	y;

	tmp = vector_sub(my_mlx->sphere->s, pos);
	t = dotproduct(dir, my_mlx->ray->v);
	p = vector_add(pos, vec_mult(dir, t));
	y = find_length(p, my_mlx->sphere->s);
	if (y < my_mlx->sphere->diameter / 2)
		return (1);
	else
		return (0);
	
}

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

unsigned	ambient_lighting(t_data *my_mlx, unsigned colour)
{
	int			r;
	int			g;
	int			b;
	t_rgb		ambient;
	unsigned	tmp;

	tmp = colour;
	r = (tmp >> 16 & 0xff);
	g = (tmp >> 8 & 0xff);
	b = (tmp & 0xff);
	ambient.r = (my_mlx->scene->amblightcolor >> 16 & 0xff);
	ambient.g = (my_mlx->scene->amblightcolor >> 8 & 0xff);
	ambient.b = (my_mlx->scene->amblightcolor & 0xff);
//printf("without amblight=%i, %i, %i\n", r, g, b);
	r *= ((double)ambient.r / 255);
	g *= ((double)ambient.g / 255);
	b *= ((double)ambient.b / 255);

//printf("with amblight=%i, %i, %i\n", r, g, b);

	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

unsigned	light_tracing(t_data *my_mlx, unsigned colour)
{
	t_vec3	pos;
	t_vec3	dir;
	t_light	*head;
	t_vec3	light;
	double	ret;

	ret = 0;
	head = my_mlx->light;
	while (my_mlx->light)
	{
		pos = vec_mult(my_mlx->ray->v, my_mlx->ray->length);
		dir = vector_sub(my_mlx->light->s, pos);
		ret = find_obstacles(my_mlx, pos, dir);
		ret *= 0.2 * my_mlx->light->brightness * fmax(0.f, dotproduct(dir, my_mlx->ray->hitnormal));
		light = vec_mult(light, ret);
//		light = vector_add(light, (ret * 0.2f * my_mlx->light->brightness * fmax(0.f, dotproduct(hitnormal, -lightdir))));
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = head;
	colour = ambient_lighting(my_mlx, colour);
	colour = colourremap01(my_mlx, my_mlx->scene->amblight);
	return (colour);
}