/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:48:51 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/17 01:41:09 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "structs.h"

/*
**Objects
*/
int			solve_quadratic_equation(t_cylhelp *help);
int			find_cylinder(t_cylinder *cyl, t_data *my_mlx, int threadnr);
int			find_cylinder_caps(t_data *my_mlx, t_cylinder *cyl,
			int threadnr, t_vec3 pos);
int			find_plane(t_plane *pl, t_data *my_mlx, int threadnr);
int			find_sphere(t_sphere *sp, t_data *my_mlx, int threadnr);
int			find_square(t_square *sq, t_data *my_mlx, int threadnr);
t_triangle	tri_rev(t_triangle t);
int			find_triangle(t_triangle *tri, t_data *my_mlx, int threadnr);

int			find_objects(t_data *my_mlx, int threadnr);

void		get_uv(t_vec3 p, double *u, double *v);
t_col		uv_checkers(t_data *my_mlx, t_sphere *sp, int threadnr);
t_col		uvmapping(t_data *my_mlx, t_sphere *sp, int threadnr);
t_vec3		bumpmapping(t_data *my_mlx, t_sphere *sp, int threadnr);

t_col		rainbow(t_data *my_mlx, t_sphere *sp, int threadnr);
t_vec3		wave(t_vec3 in);

#endif
