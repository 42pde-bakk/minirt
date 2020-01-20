/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   boat.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 13:23:26 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/20 23:52:25 by pde-bakk      ########   odam.nl         */
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

static t_matrix quat_to_matrix(double w, double x, double y, double z)
{
	t_vec3		m0;
	t_vec3		m1;
	t_vec3		m2;

	m0 = vec3_new(1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - z * w), 2.0 * (x * z + y * w));
	m1 = vec3_new(2.0 * (x * y + z * w), 1.0 - 2.0 *(x * x + z * z), 2.0 * (y * z - x * w));
	m2 = vec3_new(2.0 * (x * z - y * w), 2.0 * (y * z + x * w), 1.0 - 2.0 * (x * x + y * y));
	return (mat4_new(m0, m1, m2, vec3_new(0.0, 0.0, 1.0)));
}

static t_matrix	lookat_by_matrix(t_vec3 position, t_vec3 target)
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

static t_matrix	mat4_mulrbx(t_matrix mat, t_vec3 other)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	t;

	right = vec3_normalize(mat.r);
	up = vec3_normalize(mat.up);
	forward = vec3_normalize(mat.fw);
	t = vec3_normalize(mat.t);
	t = vec3_add(t, other);
	return (mat4_new(right, up, forward, t));
}

static t_matrix	lookat_by_quat(t_vec3 position, t_vec3 target)
{
	t_matrix	from_quat;
	t_vec3		axis;
	t_vec3		to;
	double		angle;
	double 		normal;

	to = vec3_normalize(vec3_sub(target, position));
	angle = acos(dotproduct(vec3_new(0.0, 0.0, 1.0), to));
	angle = angle * 0.5;
	axis = vec3_normalize(crossproduct(vec3_new(0.0, 0.0, 1.0), to));
	if (vec3_sqr(axis) > -EPSILON && vec3_sqr(axis) < EPSILON)
	{
		printvec(axis, "axis be on that EPSILON shit, setting to [0,1,0] now");
		axis = vec3_new(0.0, 1.0, 0.0);
	}
	// normal = sqrt(1.0 / (pow(cos(angle), 2.0) + pow(axis.x * sin(angle), 2.0) + pow(axis.y * sin(angle), 2.0) + pow(axis.z * sin(angle), 2.0)));
	// from_quat = quat_to_matrix(cos(angle) * normal, axis.x * sin(angle) * normal, axis.y * sin(angle) * normal, axis.z * sin(angle) * normal);
	return (mat4_mulrbx(from_quat, position));
}

t_matrix			mat4_lookat(t_vec3 position, t_vec3 target)
{
	t_vec3	norm;

	norm = vec3_normalize(vec3_sub(position, target));
	// printvec(norm, "normt/unit");
	if (norm.x == 0.0 && norm.z == 0.0 && (norm.y == 1.0 || norm.y == -1.0))
	{
		printf("quat quat!\n");
		return (lookat_by_quat(position, target));
	}
	else if ((norm.x == -1.0 || norm.x == 1.0) && norm.y == 0.0 && norm.z == 0.0)
	{
		printf("quat2 quat2\n");
		return (lookat_by_quat(position, target));
	}
	else
	{
		return (lookat_by_matrix(position, target));
	}
}

double	quat_sqrt(t_quat quat)
{
	double out;

	out = sqrt(quat.w * quat.w + quat.x * quat.x + quat.y * 
	quat.y + quat.z * quat.z);
	return (out);
}

t_quat	quat_norm(t_quat quat)
{
	double	m;
	t_quat	out;

	m = quat_sqrt(quat);
	out.w /= m;
	out.x /= m;
	out.y /= m;
	out.z /= m;
	return (out);
}

t_quat	quat_mult(t_quat a, t_quat b)
{
	t_quat	out;

	out.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	out.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	out.y = a.w * b.y + a.y * b.w - a.x * b.z + a.z * b.x;
	out.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
	out = quat_norm(out);
	return (out);
}

t_quat	quat_new(double w, double x, double y, double z)
{
	t_quat	out;

	out.w = w;
	out.w = x;
	out.w = y;
	out.w = z;
	return (out);
}

void	quats(void)
{
	t_quat	qx;
	t_quat	qy;
	t_quat	qz;
	t_vec3	angle;

	qx = quat_new(cos(angle.x / 2), 0.0, 0.0, sin(angle.x / 2));
	qy = quat_new(cos(angle.y / 2), 0.0, sin(angle.y / 2), 0.0);
	qz = quat_new(cos(angle.z / 2), sin(angle.z / 2), 0.0, 0.0);
}