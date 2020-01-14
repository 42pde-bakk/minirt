/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 16:06:06 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/14 11:00:45 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vector_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec3	crossproduct(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

double	dotproduct(t_vec3 v1, t_vec3 v2)
{
	double	ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vec3	vec_mult(t_vec3 v1, double d)
{
	t_vec3	ret;

	ret.x = v1.x * d;
	ret.y = v1.y * d;
	ret.z = v1.z * d;
	return (ret);
}

double	find_length(t_vec3 s, t_vec3 p)
{
	double	ret;
	double	retx;
	double	rety;
	double	retz;

	retx = pow(s.x - p.x, 2);
	rety = pow(s.y - p.y, 2);
	retz = pow(s.z - p.z, 2);
	ret = sqrt(retx + rety + retz);
	return (ret);
}

t_vec3	vec_reset(void)
{
	t_vec3 ret;

	ret.x = 0.f;
	ret.y = 0.f;
	ret.z = 0.f;
	return (ret);	
}

double	vec3_sqr(t_vec3 vec)
{
	return (pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}