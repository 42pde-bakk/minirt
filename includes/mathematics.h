/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mathematics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:45:57 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/03 17:39:05 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATICS_H
# define MATHEMATICS_H

# include "structs.h"

/*
**../src/math:
**colour.c
*/
t_col			unsigned_to_tcol(unsigned col);
t_col			colour_mult(t_col col, double c1, double c2);
t_col			colour_new(double r, double g, double b);
t_col			colour_add(t_col v1, t_col v2);
t_col			colour_mul(t_col coloura, t_col colourb, double mul);
t_col			colour_cap(t_col colour);
int				colour_check(t_col colour);
int				between_check(double check);
/*
**matrices.c
*/
void			setmatrix(t_data *my_mlx);
t_vec3			setcamera(t_data *my_mlx, double pndcx, double pndcy);
t_matrix		multmatrix(t_matrix a, t_matrix b);
t_vec3			pleurmatrix(t_vec3 v, t_matrix mat);
/*
**degrad.c
*/
double			deg2rad(double degrees);
double			rad2deg(double radians);
t_vec3			rad2degvec(t_vec3 v);
t_vec3			deg2radvec(t_vec3 v);
/*
**rotations.c
*/
t_matrix		rotate_xaxis(double camrot);
t_matrix		rotate_yaxis(double camrot);
t_matrix		rotate_zaxis(double camrot);
t_vec3			addrotation(t_vec3 lookdir, t_vec3 angle);
/*
**quaternion.c
*/
t_matrix		mat4_lookat(t_vec3 position, t_vec3 target);
t_matrix		mat4_new(t_vec3	right, t_vec3 up, t_vec3 forward, t_vec3 t);
t_matrix		mat4_angles(t_vec3 angles);

void			printquat(t_quat quat, char *str);
t_matrix		quat_to_matrix(t_quat quat);
t_quat			quat_mult(t_quat a, t_quat b);
t_quat			quat_init(double w, double x, double y, double z);
t_quat			quat_new(double x, double y, double z, double angle);
t_quat			quat_lookat(t_vec3 to, t_vec3 from);
t_matrix		lookat_by_matrix(t_vec3 position, t_vec3 target);
/*
**Vector mathematics
*/
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
double			dotproduct(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mult(t_vec3 v1, double d);
double			find_length(t_vec3 s, t_vec3 p);
t_vec3			vec3_new(double x, double y, double z);
double			vec3_sqr(t_vec3 vec);
t_vec3			vec3_normalize(t_vec3 ray);
t_vec3			crossproduct(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_perpendicular(t_vec3 v1);
t_vec3			vec3_neg(t_vec3 in);

#endif
