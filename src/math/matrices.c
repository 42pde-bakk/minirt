/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrices.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:26:29 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:26:30 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		setcamera(t_data *my_mlx, double pndcx, double pndcy)
{
	t_vec3		tmp;
	t_matrix	camtoworld;

	camtoworld = my_mlx->cam->c2w;
	tmp = vec3_new(pndcx, pndcy, -1.0);
	tmp.x *= -1;
	tmp = vec3_normalize(tmp);
	tmp = pleurmatrix(tmp, camtoworld);
	return (vec3_normalize(tmp));
}

t_matrix	multmatrix(t_matrix a, t_matrix b)
{
	t_matrix new;

	new.r.x = a.r.x * b.r.x + a.up.x * b.r.y + a.fw.x * b.r.z;
	new.r.y = a.r.y * b.r.x + a.up.y * b.r.y + a.fw.y * b.r.z;
	new.r.z = a.r.z * b.r.x + a.up.z * b.r.y + a.fw.z * b.r.z;
	new.up.x = a.r.x * b.up.x + a.up.x * b.up.y + a.fw.x * b.up.z;
	new.up.y = a.r.y * b.up.x + a.up.y * b.up.y + a.fw.y * b.up.z;
	new.up.z = a.r.z * b.up.x + a.up.z * b.up.y + a.fw.z * b.up.z;
	new.fw.x = a.r.x * b.fw.x + a.up.x * b.fw.y + a.fw.x * b.fw.z;
	new.fw.y = a.r.y * b.fw.x + a.up.x * b.fw.y + a.fw.y * b.fw.z;
	new.fw.z = a.r.y * b.fw.x + a.up.x * b.fw.y + a.fw.z * b.fw.z;
	return (new);
}

t_vec3		pleurmatrix(t_vec3 v, t_matrix mat)
{
	t_vec3	new;

	new.x = v.x * mat.r.x + v.y * mat.up.x + v.z * mat.fw.x;
	new.y = v.x * mat.r.y + v.y * mat.up.y + v.z * mat.fw.y;
	new.z = v.x * mat.r.z + v.y * mat.up.z + v.z * mat.fw.z;
	return (new);
}
