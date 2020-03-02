/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 19:24:58 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/02 13:39:10 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "structs.h"

/*
**../src/lighting:
*/
t_col	light_tracing(t_data *my_mlx, int threadnr);

int		obstaclecheck(t_data *my_mlx, t_vec3 hitpos, t_vec3 lightdir,
		double distance);

int		cylinders_loopover(t_data *my_mlx, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
int		planes_loopover(t_data *my_mlx, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
int		spheres_loopover(t_data *my_mlx, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
int		squares_loopover(t_data *my_mlx, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
int		triangles_loopover(t_data *my_mlx, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
int		obstacle_triangle(t_triangle *tri, t_vec3 hitpos,
		t_vec3 lightdir, double distance);
#endif
