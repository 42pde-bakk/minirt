/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uvmapping.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/01 16:45:02 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/03 17:19:28 by pde-bakk      ########   odam.nl         */
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

void	get_uv(t_vec3 p, double *u, double *v, t_vec3 spcenter)
{
	t_vec3	ve;
	t_vec3	vn;
	t_vec3	vp;
	double	phi;
	double	theta;

	ve = vec3_sub(vec3_new(p.x, p.y, p.z + 1), spcenter);
	ve = vec3_normalize(ve);
	vn = vec3_sub(vec3_new(p.x, p.y + 1, p.z), spcenter);
	vn = vec3_normalize(vn);
	vp = vec3_sub(p, spcenter);
	vp = vec3_normalize(vp);
	phi = acos(-dotproduct(vn, vp));
	*v = phi / M_PI;
	theta = acos(dotproduct(vp, ve)) / sin(phi) / (2.0 * M_PI);
	if (theta < 0 || theta == NAN)
		theta = 0;
	if (dotproduct(crossproduct(vn, ve), vp) > 0)
		*u = theta;
	else
		*u = 1 - theta;
}

t_col	uv_checkers(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_vec3	p;
	double	u;
	double	v;
	double	u2;
	double	v2;

	p = vec3_add(my_mlx->cam->s, vec3_mult(
		my_mlx->ray[threadnr]->v, my_mlx->ray[threadnr]->length));
	get_uv(p, &u, &v, sp->s);
	u2 = floor(u * 8);
	v2 = floor(v * 8);
	if ((int)(u2 + v2) % 2 == 0)
		return (colour_new(255, 255, 255));
	else
		return (colour_new(0.0, 0.0, 0.0));
}

t_col	uvmapping(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_col			out;
	double			u;
	double			v;
	int				i;
	int				j;

	if (my_mlx->uvimg == NULL || my_mlx->uvaddr == NULL)
		return (sp->colour);
	get_uv(vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
		my_mlx->ray[threadnr]->length)), &u, &v, sp->s);
	i = u * my_mlx->uvnx;
	j = (1 - v) * my_mlx->uvny - 0.001;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (i > my_mlx->uvnx - 1)
		i = my_mlx->uvnx - 1;
	if (j > my_mlx->uvny - 1)
		j = my_mlx->uvny - 1;
	out.r = fmax(0.0, (int)(my_mlx->uvaddr[3 * i + 3 * my_mlx->uvnx * j + 0]));
	out.g = fmax(0.0, (int)(my_mlx->uvaddr[3 * i + 3 * my_mlx->uvnx * j + 1]));
	out.b = fmax(0.0, (int)(my_mlx->uvaddr[3 * i + 3 * my_mlx->uvnx * j + 2]));
	return (out);
}
