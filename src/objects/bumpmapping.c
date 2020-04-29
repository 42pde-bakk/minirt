/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bumpmapping.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peerdb <peerdb@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 01:16:00 by peerdb        #+#    #+#                 */
/*   Updated: 2020/04/24 18:13:51 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	get_bump_colour(t_data *my_mlx, int i, int j)
{
	unsigned int	col;
	char			*image;

	image = my_mlx->bonus->bumpaddr;
	image += (j * my_mlx->bonus->bumpll + (i * (my_mlx->bonus->bumpbpp / 8)));
	col = *(unsigned int*)image;
	return (unsigned_to_tcol(col));
}

t_vec3	get_bump(t_data *my_mlx, int i, int j, t_vec3 p)
{
	t_vec3	remap;
	t_col	col;

	col = get_bump_colour(my_mlx, i, j);
//	printf("p = {%f, %f, %f}\n", p.x, p.y, p.z);
	remap = (t_vec3){p.x * (col.r / 127.5 - 1), p.y * (col.g / 127.5 - 1), p.z * (col.b / 127.5 - 1)};
//	printf("remap = {%f, %f, %f}\n", remap.x, remap.y, remap.z);
	return (remap);
}

t_vec3	bumpmapping(t_data *my_mlx, t_sphere *sp, int threadnr)
{
	t_vec3			p;
	double			u;
	double			v;
	int				i;
	int				j;

	p = vec3_normalize(vec3_sub(vec3_add(my_mlx->cam->s, vec3_mult(my_mlx->ray[threadnr]->v,
		my_mlx->ray[threadnr]->length)), sp->s));
	if (my_mlx->bonus->uvimg == NULL || my_mlx->bonus->uvaddr == NULL)
		return (p);
	get_uv(p, &u, &v);
	i = fmin(my_mlx->bonus->uvnx - 1, fmax(0.0, (my_mlx->bonus->uvnx - (u * my_mlx->bonus->uvnx))));
	j = fmin(my_mlx->bonus->uvnx - 1, fmax(0.0, (1 - v) * my_mlx->bonus->uvny - 0.001));
	return (get_bump(my_mlx, i, j, p));
}
