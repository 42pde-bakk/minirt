/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/17 23:37:46 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col		light_add(t_data *my_mlx, t_vec3 dir, int ret)
{
	t_col	hitcol;
	double	intensity;
	t_light	light;
	double	r2;
	t_col	out;

	light = *my_mlx->light;
	hitcol = my_mlx->ray->colour;
	if (ret == 0)
	{	
		r2 = vec3_sqr(dir);
		double tmp = dotproduct(my_mlx->ray->hitnormal, vec3_normalize(dir));
		intensity = fmin((light.brightness * 80 / (4.0 * M_PI * r2)) * fmax(tmp, 0.0) * ALBEDO, 1.0);
		out = colour_mul(hitcol, light.colour, intensity);
//		printf("hitcol={%f, %f, %f} & tmp=%f || intens=%f, out={%f, %f, %f}\n", hitcol.r, hitcol.g, hitcol.b, tmp, intensity, out.r, out.g, out.b);
		return (out);
	}
	else
		return (colour_new());
}

t_col	light_tracing(t_data *my_mlx)
{
	t_vec3	pos;
	t_vec3	dir;
	t_light	*head;
	t_col	total;
	int		ret;
	double	distance;

	ret = 0;
	head = my_mlx->light;
	total = colour_add(colour_new(), colour_mul(my_mlx->ray->colour, my_mlx->scene->amblightcolour, my_mlx->scene->ambintensity));
// printf("amblight gives: {%f, %f, %f}\n", total.r, total.g, total.b);
	while (my_mlx->light)
	{
		pos = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, my_mlx->ray->length));
		pos = vec3_sub(pos, vec3_mult(dir, EPSILON));
		dir = vec3_sub(my_mlx->light->s, pos);
		distance = find_length(pos, my_mlx->light->s);
		ret = find_obstacles(my_mlx, pos, dir, distance);
//		printf("totalfirst={%f,%f,%f} (so not really total tbh)\n", total.r, total.g, total.b);
		total = colour_add(total, light_add(my_mlx, dir, ret));
		// printf("total AFTER={%f,%f,%f}\n", total.r, total.g, total.b);
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = head;
	return (total);
}