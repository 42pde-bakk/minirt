/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rainbow.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:44 by peer          #+#    #+#                 */
/*   Updated: 2020/05/06 06:27:13 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	rainbow(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_vec3	p;
	double	u;
	double	v;
	double	u2;

	p = vec3_sub(vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
		my_mlx->ray[threadnr]->length)), sp->s);
	get_uv(p, &u, &v);
	u2 = floor(u * 7 * 10);
	if ((int)u2 % 7 == 0)
		return (colour_new(255, 0, 0));
	else if ((int)u2 % 7 == 1)
		return (colour_new(255, 127, 0));
	else if ((int)u2 % 7 == 2)
		return (colour_new(255, 255, 0));
	else if ((int)u2 % 7 == 3)
		return (colour_new(0, 255, 0));
	else if ((int)u2 % 7 == 4)
		return (colour_new(0, 0, 255));
	else if ((int)u2 % 7 == 5)
		return (colour_new(46, 43, 95));
	else
		return (colour_new(139, 0, 255));
}
