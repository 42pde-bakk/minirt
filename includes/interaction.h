/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:41:53 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/06 21:30:41 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H

# include "structs.h"

int					keyinput(int keycode, t_data *my_mlx);
int					ripwindow(t_data *my_mlx);

int					mouseinput(int button, int x, int y, t_data *my_mlx);
double				click_cylinder(t_cylinder *cyl, t_data *my_mlx, t_vec3 ray);
double				click_plane(t_plane *pl, t_data *my_mlx, t_vec3 ray);
double				click_sphere(t_sphere *sp, t_data *my_mlx, t_vec3 ray);
double				click_triangle(t_triangle *tri, t_data *my_mlx, t_vec3 ray);
double				click_square(t_square *sq, t_data *my_mlx, t_vec3 ray);
int					click_object(t_data *my_mlx, t_vec3 ray);

int					sphere_edit_properties(t_data *my_mlx, double distancex, double distancey);
int					triangle_edit_properties(t_data *my_mlx, double distancex, double distancey);
int					square_edit_properties(t_data *my_mlx, double distx, double disty);
int					plane_edit_properties(t_data *my_mlx, double distx, double disty);
int					cylinder_edit_properties(t_data *my_mlx, double distx, double disty);

void				get_click_info(int x, int y, t_data *my_mlx);
#endif