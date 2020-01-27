/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degrad.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 16:24:53 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/19 08:48:26 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double rad2deg(double radians)
{
	return (radians * (180 / M_PI));
}

t_vec3	deg2radvec(t_vec3 v)
{
	v.x *= (M_PI / 180.0);
	v.y *= (M_PI / 180.0);
	v.z *= (M_PI / 180.0);
	return (v);
}

t_vec3	rad2degvec(t_vec3 v)
{
	v.x *= (180.0 / M_PI);
	v.y *= (180.0 / M_PI);
	v.z *= (180.0 / M_PI);
	return (v);
}
