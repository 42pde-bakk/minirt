/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrices.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:16:13 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/18 14:15:59 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		vec3multmatrix(t_vec3 v, t_matrix m)
{
	t_vec3	out;
	
	out.x = v.x * m.r.x + v.y * m.up.x + v.z * m.fw.x + m.t.x;
	out.y = v.x * m.r.y + v.y * m.up.y + v.z * m.fw.y + m.t.y;
	out.z = v.x * m.r.z + v.y * m.up.z + v.z * m.fw.z + m.t.z;
	return (out);
}

t_vec3		multdirmatrix(t_vec3 src, t_matrix mat)
{
	t_vec3	out;

	out.x = src.x * mat.r.x + src.y * mat.up.x + src.z * mat.fw.x;
	out.y = src.x * mat.r.y + src.y * mat.up.y + src.z * mat.fw.y;
	out.z = src.x * mat.r.z + src.y * mat.up.z + src.z * mat.fw.z;
	return (out);
}

void		printvec(t_vec3	v, char *s)
{
	printf("vector %s={%f, %f, %f}\n", s, v.x, v.y, v.z);
}

t_matrix	setmatrix(t_data *my_mlx)
{
	t_matrix	camtoworld;
	t_vec3		tmp;

	tmp = vec3_add(my_mlx->cam->s, my_mlx->cam->v);
	printvec(my_mlx->cam->s, "cam->s");
	printvec(my_mlx->cam->v, "cam->v");
	camtoworld.fw = vec3_normalize(vec3_sub(my_mlx->cam->s, tmp));
	printvec(camtoworld.fw, "c2w.fw");
	camtoworld.r = crossproduct(vec3_new(0.0, 1.0, 0.0), camtoworld.fw);
	camtoworld.up = crossproduct(camtoworld.fw, camtoworld.r);
	camtoworld.t = my_mlx->cam->s;
	return (camtoworld);
}

void	setcamera(t_data *my_mlx, double pndcx, double pndcy, t_matrix camtoworld)
{
	t_vec3	tmp;

	tmp = vec3_new(pndcx, pndcy, -1.0);
	my_mlx->ray->v = multdirmatrix(tmp, camtoworld);
	my_mlx->ray->v.x *= -1;
	my_mlx->ray->v = vec3_normalize(my_mlx->ray->v);
}