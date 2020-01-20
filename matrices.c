/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrices.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 18:16:13 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/20 20:25:21 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	// moet er uit (check ook op #include <stdio.h> aub)
}

void		printmatrix(t_matrix v)
{
	printvec(v.r, "right");
	printvec(v.up, "up");
	printvec(v.fw, "forward");
	printvec(v.t, "t");
}

// t_matrix	lookat(t_data *my_mlx)
// {

// }

// t_matrix	lookat_by_quat(t_data *my_mlx)
// {
// 	t_matrix	from_quat;
// 	t_vec3		axis;
// 	t_vec3		forward;
// 	t_vec3		to;
// 	double		angle;
// 	double		normal;

// 	forward = vec3_new(0.0, 0.0, 1.0);
// 	to = vec3_mult(my_mlx->cam->v, -1);
// 	angle = acos(dotproduct())
// }

// void		setmatrix(t_data *my_mlx)
// {
// 	t_matrix	camtoworld;
// 	t_vec3		tmp;

// 	tmp = vec3_add(my_mlx->cam->s, my_mlx->cam->v);
// 	// printvec(my_mlx->cam->s, "cam->s");
// 	// printvec(my_mlx->cam->v, "cam->v");
// 	camtoworld.fw = vec3_normalize(vec3_sub(my_mlx->cam->s, tmp));
// 	// printvec(camtoworld.fw, "c2w.fw");
// 	camtoworld.r = crossproduct(vec3_new(0.0, 1.0, 0.0), camtoworld.fw);
// 	camtoworld.up = crossproduct(camtoworld.fw, camtoworld.r);
// 	camtoworld.t = my_mlx->cam->s;
// 	my_mlx->cam->c2w = camtoworld;
// 	printvec(camtoworld.r, "c2w.r");
// 	printvec(camtoworld.up, "c2w.up");
// 	printvec(camtoworld.fw, "c2w.fw");
// 	printvec(camtoworld.t, "c2w.t");
// }

void	setcamera(t_data *my_mlx, double pndcx, double pndcy)
{
	t_vec3		tmp;
	t_matrix	camtoworld;

	camtoworld = my_mlx->cam->c2w;
	tmp = vec3_new(pndcx, pndcy, -1.0);
	my_mlx->ray->v = multdirmatrix(tmp, camtoworld);
	my_mlx->ray->v.x *= -1;
	my_mlx->ray->v = vec3_normalize(my_mlx->ray->v);
}

t_matrix	rotx(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(1, 0, 0);
	mat.up = vec3_new(0, cos(rot), -sin(rot));
	mat.fw = vec3_new(0, sin(rot), cos(rot));
	return (mat);
}

t_matrix	roty(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(cos(rot), 0, sin(rot));
	mat.up = vec3_new(0, 1, 0);
	mat.fw = vec3_new(-sin(rot), 0, cos(rot));
	return (mat);
}

t_matrix	rotz(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(cos(rot), -sin(rot), 0);
	mat.up = vec3_new(sin(rot), cos(rot), 0);
	mat.fw = vec3_new(0, 0, 1);
	printf("rotz matrix=\n");
	printmatrix(mat);
	return (mat);
}

t_matrix	rotate(t_vec3 angle)
{
	t_matrix	out;

	out = multmatrix(rotx(angle.x), roty(angle.y));
	out = multmatrix(out, rotz(angle.z));
	return (out);
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

