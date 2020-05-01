/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sphere.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:14 by peer          #+#    #+#                 */
/*   Updated: 2020/05/01 15:15:41 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_hit(t_sphere *sp, t_data *my_mlx, int threadnr, double t)
{
	if (t < my_mlx->ray[threadnr]->length)
	{
		my_mlx->ray[threadnr]->length = t;
		my_mlx->ray[threadnr]->hitnormal = vec3_normalize(vec3_sub(vec3_add(
			my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v, t)), sp->s));
		if (BONUS == 1 && BUMP == 1)
			my_mlx->ray[threadnr]->hitnormal =
				bumpmapping(my_mlx, sp, threadnr);
		if (BONUS == 1 && WAVE == 1)
			my_mlx->ray[threadnr]->hitnormal =
				wave(my_mlx->ray[threadnr]->hitnormal);
		if (BONUS == 1 && RAINBOW == 1)
			my_mlx->ray[threadnr]->colour = rainbow(my_mlx, sp, threadnr);
		else if (BONUS == 1 && UV == 0)
			my_mlx->ray[threadnr]->colour = uv_checkers(my_mlx, sp, threadnr);
		else if (BONUS == 1 && (UV == 1 || UV == 2) &&
				my_mlx->bonus->uvimg != NULL)
			my_mlx->ray[threadnr]->colour = uvmapping(my_mlx, sp, threadnr);
		else
			my_mlx->ray[threadnr]->colour = sp->colour;
	}
}

int		find_sphere(t_sphere *sp, t_data *my_mlx, int threadnr)
{
	t_vec3	p;
	double	tc[2];
	double	d2;
	double	t[3];

	p = vec3_sub(sp->s, my_mlx->cam->s);
	tc[0] = dotproduct(p, my_mlx->ray[threadnr]->v);
	if (tc[0] < 0)
		return (0);
	d2 = dotproduct(p, p) - pow(tc[0], 2);
	if (d2 > pow(sp->diameter / 2, 2))
		return (0);
	tc[1] = sqrt(pow(sp->diameter / 2, 2) - d2);
	t[0] = tc[0] - tc[1];
	t[1] = tc[0] + tc[1];
	if (t[0] > t[1])
		fswap(&t[0], &t[1]);
	if (t[0] < 0)
	{
		t[0] = t[1];
		if (t[0] < 0)
			return (0);
	}
	sphere_hit(sp, my_mlx, threadnr, t[0]);
	return (1);
}
