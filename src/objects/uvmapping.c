/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uvmapping.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/01 16:45:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/17 01:29:05 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	uv_pattern_at(double u, double v, int width, int height)
{
	double	u2;
	double	v2;

	u2 = floor(u * width);
	v2 = floor(v * height);
	if ((int)(u2 + v2) % 2 == 0.0)
		return (colour_new(0.0, 0.0, 0.0));
	else
		return (colour_new(255, 255, 255));
}

void	get_uv(t_vec3 p, double *u, double *v)
{
	double	phi;
	double	theta;

	p = vec3_normalize(p);
	phi = atan2(p.z, p.x);
	theta = asin(p.y);
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

t_col	uv_checkers(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_vec3	p;
	double	u;
	double	v;
	double	u2;
	double	v2;

	p = vec3_sub(vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
		my_mlx->ray[threadnr]->length)), sp->s);
	get_uv(p, &u, &v);
	u2 = floor(u * 8);
	v2 = floor(v * 8);
	if ((int)(u2 + v2) % 2 == 0)
		return (colour_new(255, 255, 255));
	else
		return (colour_new(0.0, 0.0, 0.0));
}

t_col	get_colour(t_data *my_mlx, int i, int j)
{
	unsigned int	col;
	char			*image;

	image = my_mlx->bonus->uvaddr;
	image += (j * my_mlx->bonus->uvll + (i * (my_mlx->bonus->uvbpp / 8)));
	col = *(unsigned int*)image;
	return (unsigned_to_tcol(col));
}

t_col	uvmapping(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_col			out;
	double			u;
	double			v;
	int				i;
	int				j;

	if (my_mlx->bonus->uvimg == NULL || my_mlx->bonus->uvaddr == NULL)
		return (sp->colour);
	get_uv(vec3_sub(vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
		my_mlx->ray[threadnr]->length)), sp->s), &u, &v);
	i = fmin(my_mlx->bonus->uvnx - 1, fmax(0.0, (my_mlx->bonus->uvnx - (u * my_mlx->bonus->uvnx))));
	j = fmin(my_mlx->bonus->uvnx - 1, fmax(0.0, (1 - v) * my_mlx->bonus->uvny - 0.001));
	out = get_colour(my_mlx, i, j);
	return (out);
}
