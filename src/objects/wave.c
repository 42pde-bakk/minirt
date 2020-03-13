/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wave.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 15:02:18 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/12 15:03:46 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	wave(t_vec3 in)
{
	t_vec3	out;

	out.x = sin(in.x);
	out.y = sin(in.y);
	out.z = sin(in.z);
	return (out);
}
