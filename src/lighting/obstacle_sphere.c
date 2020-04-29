/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacle_sphere.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:05:37 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:52:40 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	obstacle_sphere(t_sphere *sp, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	t_vec3	sub;
	double	t;
	double	y;
	t_vec3	p;

	sub = vec3_sub(sp->s, hitpos);
	t = dotproduct(sub, lightdir);
	if (t < 0 || t > distance)
		return (0);
	p = vec3_add(hitpos, vec3_mult(lightdir, t));
	y = find_length(p, sp->s);
	if (y < sp->diameter / 2 && y >= 0.0)
		return (1);
	return (0);
}

int	spheres_loopover(t_data *my_mlx, t_vec3 hitpos,
	t_vec3 lightdir, double distance)
{
	t_sphere	*tmpsphere;

	tmpsphere = my_mlx->sphere;
	while (tmpsphere)
	{
		if (obstacle_sphere(tmpsphere, hitpos, lightdir, distance) == 1)
			return (1);
		tmpsphere = tmpsphere->next;
	}
	return (0);
}
