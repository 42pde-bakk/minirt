/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mat4_lookat.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 20:26:41 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 20:26:56 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	mat4_new(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 t)
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
	return (mat4_new(right, up, forward, position));
}

t_matrix	mat4_lookat(t_vec3 position, t_vec3 target)
{
	t_vec3		norm;
	t_matrix	mat;

	norm = vec3_normalize(vec3_sub(target, position));
	if (norm.x == 0.0 && norm.z == 0.0 && fabs(norm.y) == 1.0)
	{
		if (norm.y == 1.0)
		{
			mat.r = vec3_new(1.0, 0.0, 0.0);
			mat.up = vec3_new(0.0, 0.0, 1.0);
			mat.fw = vec3_new(0.0, 1.0, 0.0);
		}
		else
		{
			mat.r = vec3_new(0.0, 0.0, 1.0);
			mat.up = vec3_new(1.0, 0.0, 0.0);
			mat.fw = vec3_new(0.0, -1.0, 0.0);
		}
		mat.t = position;
		return (mat);
	}
	else
		return (lookat_by_matrix(position, target));
}
