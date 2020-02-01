/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrices.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:16:13 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/31 20:53:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	mat4_new(t_vec3	right, t_vec3 up, t_vec3 forward, t_vec3 t)
{
	t_matrix newmatrix;

	newmatrix.r = right;
	newmatrix.up = up;
	newmatrix.fw = forward;
	newmatrix.t = t;
	return (newmatrix);
}

t_matrix	lookat_by_matrix(t_vec3 position, t_vec3 target)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	stdup;

	stdup = vec3_new(0.0, 1.0, 0.0);
	forward = vec3_normalize(vec3_sub(position, target));
	right = crossproduct(stdup, forward);
	up = crossproduct(forward, right);
	// printvec(up, "lookat by matrix upvector");
	return (mat4_new(right, up, forward, position));
}

t_matrix			mat4_lookat(t_vec3 position, t_vec3 target)
{
	t_vec3	norm;

	norm = vec3_normalize(vec3_sub(position, target));
	if (norm.x == 0.0 && norm.z == 0.0 && fabs(norm.y) == 1.0)
		return (quat_to_matrix(quat_lookat(position, target)));
	else
		return (lookat_by_matrix(position, target));
}

void		printvec(t_vec3	v, char *s)
{
	printf("vector %s={%f, %f, %f}\n", s, v.x, v.y, v.z);
	// moet er uit (check ook op #include <stdio.h> aub)
}

void		printmatrix(t_matrix v)
{
	printvec(v.r, "right");
	printvec(v.up, "up");
	printvec(v.fw, "forward");
	printvec(v.t, "t");
}

void	setcamera(t_data *my_mlx, double pndcx, double pndcy)
{
	t_vec3		tmp;
	t_matrix	camtoworld;

	camtoworld = my_mlx->cam->c2w;
	tmp = vec3_new(pndcx, pndcy, -1.0);
	tmp.x *= -1;
	tmp = vec3_normalize(tmp);
	my_mlx->ray->v = pleurmatrix(tmp, camtoworld);
	my_mlx->ray->v = vec3_normalize(my_mlx->ray->v);
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

t_matrix	addmatrix(t_matrix a, t_matrix b)
{
	t_matrix	out;

	out.r = vec3_normalize(vec3_add(a.r, b.r));
	out.up = vec3_normalize(vec3_add(a.up, b.up));
	out.fw = vec3_normalize(vec3_add(a.fw, b.fw));
	return (out);
}

t_vec3	pleurmatrix(t_vec3 v, t_matrix mat)
{
	t_vec3	new;

	new.x = v.x * mat.r.x + v.y * mat.up.x + v.z * mat.fw.x;
	new.y = v.x * mat.r.y + v.y * mat.up.y + v.z * mat.fw.y;
	new.z = v.x * mat.r.z + v.y * mat.up.z + v.z * mat.fw.z;
	return (new);
}
