/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:26:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/17 14:12:24 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		plane_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	double	a;
	double	denom;
	double	t;

	tmp = vector_sub(my_mlx->plane->s, pos);
	denom = dotproduct(my_mlx->plane->normal, dir);
	if (denom > 0.000001)
	{
		a = dotproduct(tmp, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0)
			return (1);
	}
	return (0);
}

int		sphere_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir, double distance)
{
	t_vec3	l;
	double	tca;

	l = vector_sub(my_mlx->sphere->s, pos);
	tca = dotproduct(l, dir);
	if (tca < 0)
		return (0);
	double	d2 = dotproduct(l, l) - tca * tca;
	if (d2 > pow(my_mlx->sphere->diameter / 2, 2))
		return (0);
	double thc = sqrt(my_mlx->sphere->diameter / 2 - d2);
	if (distance < tca - thc)
		return (0);
	else
		return (1);
	// t = dotproduct(dir, my_mlx->ray->v);
	// p = vector_add(pos, vec_mult(dir, t));
	// y = find_length(p, my_mlx->sphere->s);
}

int			find_obstacles(t_data *my_mlx, t_vec3 pos, t_vec3 dir, double distance)
{
	t_sphere	*head;
	int			ret;

	ret =  0;
	head = my_mlx->sphere;
//	pos = vector_sub(pos, vec_mult(dir, EPSILON));
	dir = normalize_ray(dir);
	while (my_mlx->sphere && ret == 0)
	{
		ret = sphere_obs(my_mlx, pos, dir, distance);
		my_mlx->sphere = my_mlx->sphere->next;
// gotta add a check to see if the obstacle is further away than raydir
	}
	my_mlx->sphere = head;
	return (ret);
}