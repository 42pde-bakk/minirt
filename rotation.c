/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotation.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/19 08:42:22 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/19 08:46:43 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
 
t_vec3	rx(t_vec3 v, double x)
{
	t_vec3	new;

	new.x = v.x;
	new.y = v.y * cos(x) - v.z * sin(x);
	new.z = v.y * sin(x) + v.z * cos(x);
	return (new);
}

t_vec3	ry(t_vec3 v, double y)
{
	t_vec3	new;

	new.x = v.x * cos(y) + v.z * sin(y);
	new.y = v.y;
	new.z = v.x * -sin(y) + v.z * cos(y);
	return (new);
}

t_vec3	rz(t_vec3 v, double z)
{
	t_vec3	new;
	new.x = v.x * cos(z) - v.y * sin(z);
	new.y = v.x * sin(z) + v.y * cos(z);
	new.z = v.z;
	return (new);
}

t_vec3	rot(t_vec3 v, t_vec3 angle)
{
	t_vec3	new;

	angle = deg2radvec(angle);
	new = rx(v, angle.x);
	new = ry(v, angle.y);
	new = rz(v, angle.z);
	return (new);
}

t_vec3	antirot(t_vec3 v, t_vec3 angle)
{
	t_vec3	new;

	new = rz(v, -angle.z);
	new = ry(v, -angle.y);
	new = rx(v, -angle.x);
	return (new);
}
