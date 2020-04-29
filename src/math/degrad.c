/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degrad.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:27:42 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:27:43 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	rad2deg(double radians)
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
