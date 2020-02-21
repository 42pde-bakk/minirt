/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mat4_angles.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 17:26:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 20:30:10 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_matrix	x_angle(double x)
{
	x = fmod(x, M_PI * 2);
	return (mat4_new(vec3_new(0.0, 0.0, 1.0),
			vec3_new(0.0, cos(x), -sin(x)),
			vec3_new(0.0, sin(x), cos(x)),
			vec3_new(0.0, 0.0, 0.0)));
}

static t_matrix	y_angle(double y)
{
	y = fmod(y, M_PI * 2);
	return (mat4_new(vec3_new(cos(y), 0.0, sin(y)),
			vec3_new(0.0, 1.0, 0.0),
			vec3_new(-sin(y), 0.0, cos(y)),
			vec3_new(0.0, 0.0, 0.0)));
}

static t_matrix	z_angle(double z)
{
	z = fmod(z, M_PI * 2);
	return (mat4_new(vec3_new(cos(z), -sin(z), 0.0),
			vec3_new(sin(z), cos(z), 0.0),
			vec3_new(0.0, 0.0, 1.0),
			vec3_new(0.0, 0.0, 0.0)));
}

t_matrix		mat4_angles(t_vec3 angles)
{
	t_matrix	tmp;
	t_matrix	out;

	tmp = multmatrix(x_angle(angles.x), y_angle(angles.y));
	out = multmatrix(tmp, z_angle(angles.z));
	return (out);
}

int				between_check(double check)
{
	if (check < 0.0 || check > 1.0)
		return (0);
	return (1);
}
