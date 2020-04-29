/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacle_plane.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:04:50 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:52:38 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	obstacle_plane(t_plane *pl, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	t_vec3	tmp;
	double	a;
	double	denom;
	double	t;

	tmp = vec3_sub(pl->s, hitpos);
	denom = dotproduct(pl->normal, lightdir);
	if (denom > 0.000001)
	{
		a = dotproduct(tmp, pl->normal);
		t = a / denom;
		if (t > 0 && t < distance)
		{
			return (1);
		}
	}
	return (0);
}

int	planes_loopover(t_data *my_mlx, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	t_plane	*tmpplane;

	tmpplane = my_mlx->plane;
	while (tmpplane)
	{
		if (obstacle_plane(tmpplane, hitpos, lightdir, distance) == 1)
			return (1);
		tmpplane = tmpplane->next;
	}
	return (0);
}
