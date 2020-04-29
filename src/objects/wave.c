/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wave.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:14:50 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:14:51 by peer          ########   odam.nl         */
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
