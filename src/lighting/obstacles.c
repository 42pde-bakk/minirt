/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obstacles.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:26:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/02 20:42:21 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		plane_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir, double distance)
{
	t_vec3	tmp;
	double	a;
	double	denom;
	double	t;

	tmp = vec3_sub(my_mlx->plane->s, pos);
	denom = dotproduct(my_mlx->plane->normal, dir);
	if (denom > 0.000001)
	{
		a = dotproduct(tmp, my_mlx->plane->normal);
		t = a / denom;
		if (t > 0 && t < distance)
		{
			return (1);
		}
	}
	return (0);
}

int		sphere_obs(t_data *my_mlx, t_vec3 hitpos, t_vec3 dir, double distance)
{
	t_vec3	l;
	double	tca;
	double	d2;
	double	thc;

	l = vec3_sub(hitpos, my_mlx->sphere->s);
	tca = dotproduct(l, dir);
	if (tca < 0)
		return (0);
	d2 = dotproduct(l, l) - tca * tca;
	if (d2 > pow(my_mlx->sphere->diameter / 2, 2))
		return (0);
	thc = sqrt(my_mlx->sphere->diameter / 2 - d2);
	if (tca - thc < distance && tca - thc > 0)
	{
//		printf("obj found\n");
		return (0);
	}
	else
		return (1);
}

int		find_objects1(t_data *my_mlx, t_vec3 hitpos, t_vec3 ldir, double lhdist)
{
	int			ret;
	t_sphere	*spherehead;

	spherehead = my_mlx->sphere;
	ret = 0;
	while (my_mlx->sphere && ret == 0)
	{
		ret = sphere_obs(my_mlx, hitpos, ldir, lhdist);
//		ret = 0;
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = spherehead;
	return (ret);
}

int		find_obstacles(t_data *my_mlx, t_vec3 ldir, t_vec3 hitpos)
{
	int	ret;
	double	lhdist;

	ldir = vec3_normalize(ldir);
	lhdist = find_length(hitpos, my_mlx->light->s);
	ret = find_objects1(my_mlx, hitpos, ldir, lhdist);
	return (ret);
}
