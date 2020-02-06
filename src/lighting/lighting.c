/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/05 20:10:42 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_col	add_light(t_data *my_mlx, t_light *light_current, t_vec3 lightdir)
{
	double	dotnormal;
	double	intensity;
	double	r2;
	
	r2 = vec3_sqr(lightdir);
	dotnormal = fmax(0.0, dotproduct(my_mlx->ray->hitnormal, lightdir));
//	printf("dotnormal=%f\n", dotnormal);
	intensity = fmin(1.0, light_current->brightness / (4.0 * M_PI * r2) * dotnormal * 4 * ALBEDO);
	return (colour_mul(my_mlx->ray->colour, light_current->colour, intensity));
}

t_col	light_tracing(t_data *my_mlx)
{
	t_col	out;
	t_light	*tmplight;
	t_vec3	hitpos;
	t_vec3	lightdir;

	tmplight = my_mlx->light;
	out = colour_new(0.0, 0.0, 0.0);
	out = colour_mul(my_mlx->ray->colour, my_mlx->scene->amblightcolour, my_mlx->scene->ambintensity);
	hitpos = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, my_mlx->ray->length - EPSILON));
	while (tmplight)
	{
		lightdir = vec3_sub(tmplight->s, hitpos);
		out = colour_add(out, add_light(my_mlx, tmplight, lightdir));
		tmplight = tmplight->next;
	}
	out = colour_cap(out);
	return (out);
}