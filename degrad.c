/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   degrad.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 16:24:53 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/01/18 16:26:28 by Peer de Bak   ########   odam.nl         */
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
