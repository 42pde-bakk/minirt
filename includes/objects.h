/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:48:51 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/11 16:17:01 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "structs.h"

/*
**Objects
*/
int			solve_quadratic_equation(t_cylhelp *help);
int			find_cylinder(t_cylinder *cyl, t_data *my_mlx);
int			find_plane(t_plane *pl, t_data *my_mlx);
int			find_sphere(t_sphere *sp, t_data *my_mlx);
int			find_square(t_square *sq, t_data *my_mlx);
t_triangle	tri_rev(t_triangle t);
int			find_triangle(t_triangle *tri, t_data *my_mlx);

int			find_objects(t_data *my_mlx);

#endif
