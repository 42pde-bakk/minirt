/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors_adv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 23:32:34 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/27 19:50:25 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_normalize(t_vec3 ray)
{
	t_vec3	ret;
	double	length;

	ret = ray;
	length = sqrt((ray.x * ray.x) + (ray.y * ray.y) + (ray.z * ray.z));
	ret.x /= length;
	ret.y /= length;
	ret.z /= length;
	// length = sqrt((ray.x * ray.x) + (ray.y * ray.y) + (ray.z * ray.z));
	// printf("ray={%f, %f, %f} legnth=%f\n", ray.x, ray.y, ray.z, length);
	return (ret);
}

t_vec3	vec3_mult(t_vec3 v1, double d)
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

double	vec3_sqr(t_vec3 vec)
{
	return (pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

