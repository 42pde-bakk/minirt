/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quaternions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 13:23:26 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/17 02:55:46 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	quat_to_matrix(t_quat quat)
{
	t_matrix	new;
	double		w;
	double		x;
	double		y;
	double		z;

	w = quat.w;
	x = quat.x;
	y = quat.y;
	z = quat.z;
	new.r.x = w * w + x * x - y * y - z * z;
	new.r.y = 2 * x * y - 2 * w * z;
	new.r.z = 2 * x * z + 2 * w * y;
	new.up.x = 2 * x * y + 2 * w * z;
	new.up.y = w * w - x * x + y * y - z * z;
	new.up.z = 2 * y * z + 2 * w * x;
	new.fw.x = 2 * x * z - 2 * w * y;
	new.fw.y = 2 * y * z - 2 * w * x;
	new.fw.z = w * w - x * x - y * y + z * z;
	return (new);
}

double		quat_sqrt(t_quat quat)
{
	double out;

	out = sqrt(quat.w * quat.w + quat.x * quat.x + quat.y *
	quat.y + quat.z * quat.z);
	return (out);
}

t_quat		quat_norm(t_quat quat)
{
	double	m;

	m = quat_sqrt(quat);
	quat.w /= m;
	quat.x /= m;
	quat.y /= m;
	quat.z /= m;
	return (quat);
}

t_quat		quat_mult(t_quat a, t_quat b)
{
	t_quat	new;

	new.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	new.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	new.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	new.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (new);
}

t_quat		quat_init(double w, double x, double y, double z)
{
	t_quat	out;

	out.w = w;
	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}
