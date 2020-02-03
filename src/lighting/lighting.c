/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 11:42:47 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/03 19:39:25 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_col	light_add(t_data *my_mlx, t_col out, t_vec3 ldir)
{
	double	intensity;
	double	dotnormal;
	double	r2;
	t_vec3	invdir;

	r2 = vec3_sqr(ldir);
	invdir = vec3_normalize(vec3_mult(ldir, -1.0));
	dotnormal = fmax(0.0, dotproduct(my_mlx->ray->hitnormal, invdir));
	intensity = fmin(1.0, my_mlx->light->brightness / (4.0 * M_PI * r2) * dotnormal * ALBEDO * 10);
//	printf("intensity=%f cus dotnormal =%f, with r2=%f\n", intensity, dotnormal, r2);
//	printvec(ldir, "ldir");
	return (colour_add(out, colour_mul(my_mlx->ray->colour, my_mlx->light->colour, intensity)));
}

t_col	light_tracing(t_data *my_mlx)
{
	t_light	*headlight;
	t_vec3	hitpos;
	t_vec3	ldir;
	t_col	out;
	int		ret;

	headlight = my_mlx->light;
	out = colour_mul(my_mlx->ray->colour, my_mlx->scene->amblightcolour, my_mlx->scene->ambintensity);
	hitpos = vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray->v, my_mlx->ray->length - EPSILON));
	while (my_mlx->light)
	{
		ldir = vec3_sub(hitpos, my_mlx->light->s);
//		ret = find_obstacles(my_mlx, ldir, hitpos);
		ret = 0;
		if (ret == 0)
			out = light_add(my_mlx, out, ldir);
		// ldir = vec3_sub(my_mlx->light->s, hitpos);
		// if (ret == 0)
		// 	out = light_add(my_mlx, out, ldir);
		my_mlx->light = my_mlx->light->next;
	}
	my_mlx->light = headlight;
	out = colour_cap(out);
	return (out);
}