/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   objects.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:15:17 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:15:18 by peer          ########   odam.nl         */
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
