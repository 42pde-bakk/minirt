/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotations.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/25 19:08:55 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 17:54:33 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	rotate_xaxis(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(1, 0, 0);
	mat.up = vec3_new(0, cos(rot), sin(rot));
	mat.fw = vec3_new(0, -sin(rot), cos(rot));
	return (mat);
}

t_matrix	rotate_yaxis(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(cos(rot), 0, -sin(rot));
	mat.up = vec3_new(0, 1, 0);
	mat.fw = vec3_new(sin(rot), 0, cos(rot));
	return (mat);
}

t_matrix	rotate_zaxis(double camrot)
{
	double		rot;
	t_matrix	mat;

	rot = deg2rad(camrot);
	mat.r = vec3_new(cos(rot), sin(rot), 0);
	mat.up = vec3_new(-sin(rot), cos(rot), 0);
	mat.fw = vec3_new(0, 0, 1);
	return (mat);
}

t_vec3		addrotation(t_vec3 lookdir, t_vec3 angle)
{
	if (angle.x > 0.0 || angle.x < 0.0)
		lookdir = pleurmatrix(lookdir, rotate_xaxis(angle.x));
	if (angle.y > 0.0 || angle.y < 0.0)
		lookdir = pleurmatrix(lookdir, rotate_yaxis(angle.y));
	if (angle.z > 0.0 || angle.z < 0.0)
		lookdir = pleurmatrix(lookdir, rotate_zaxis(angle.z));
	return (lookdir);
}
