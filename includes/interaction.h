/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interaction.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 17:34:30 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 17:46:21 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H

# include "structs.h"

int		keyinput(int keycode, t_data *my_mlx);
int		ripwindow(t_data *my_mlx);
void	object_change_rotsize(int keycode, t_data *my_mlx);

int		mouseinput(int button, int x, int y, t_data *my_mlx);

void	arrowkeys(int keycode, t_data *my_mlx);
void	wasd(int keycode, t_data *my_mlx);
int		get_object_cylinder(t_data *my_mlx, t_vec3 ray);
int		get_object_plane(t_data *my_mlx, t_vec3 ray);

double	click_cylinder(t_cylinder *cyl, t_data *my_mlx, t_vec3 ray);
double	click_plane(t_plane *pl, t_data *my_mlx, t_vec3 ray);
double	click_sphere(t_sphere *sp, t_data *my_mlx, t_vec3 ray);
double	click_triangle(t_triangle *tri, t_data *my_mlx, t_vec3 ray);
double	click_square(t_square *sq, t_data *my_mlx, t_vec3 ray);
int		click_object(t_data *my_mlx, t_vec3 ray);

t_vec3	obj_move(t_vec3 pos, t_data *my_mlx);
int		sphere_edit_properties(t_data *my_mlx);
int		triangle_edit_properties(t_data *my_mlx);
int		square_edit_properties(t_data *my_mlx);
int		plane_edit_properties(t_data *my_mlx);
int		cylinder_edit_properties(t_data *my_mlx);
int		object_edit_properties(t_data *my_mlx);

void	get_click_info(int x, int y, t_data *my_mlx);
#endif
