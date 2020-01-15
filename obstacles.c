/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:26:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/15 22:20:24 by Peer de Bak   ########   odam.nl         */
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

int		sphere_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_vec3	tmp;
	t_vec3	p;
	double	t;
	double	y;

	tmp = vector_sub(my_mlx->sphere->s, pos);
	t = dotproduct(dir, my_mlx->ray->v);
	p = vector_add(pos, vec_mult(dir, t));
	y = find_length(p, my_mlx->sphere->s);
	if (y < my_mlx->sphere->diameter / 2)
		return (1);
	else
		return (0);
}

int			find_obstacles(t_data *my_mlx, t_vec3 pos, t_vec3 dir)
{
	t_sphere	*head;
	int			ret;

	ret =  0;
	head = my_mlx->sphere;
	pos = vector_sub(pos, vec_mult(dir, EPSILON));
	dir = normalize_ray(dir);
	while (my_mlx->sphere && ret == 0)
	{
		ret = sphere_obs(my_mlx, pos, dir);
		my_mlx->sphere = my_mlx->sphere->next;
// gotta add a check to see if the obstacle is further away than raydir
	}
	my_mlx->sphere = head;
	return (ret);
}