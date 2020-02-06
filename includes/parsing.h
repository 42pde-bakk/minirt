/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:47:11 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/06 16:48:12 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"

int		parse_camera(t_data *my_mlx, char *line, int *i);
int		parse_light(t_data *my_mlx, char *line, int *i);
int		parse_cylinder(t_data *my_mlx, char *line, int *i);
int		parse_plane(t_data *my_mlx, char *line, int *i);
int		parse_sphere(t_data *my_mlx, char *line, int *i);
int		parse_square(t_data *my_mlx, char *line, int *i);
int		parse_triangle(t_data *my_mlx, char *line, int *i);

t_col	parse_tcol(char *line, int *i);
int		parse_objects(t_data *my_mlx, char *line, int *i);
int		find_res_amb_cam_light(t_data *my_mlx, char *line, int *i);
void	ft_parser(t_data *my_mlx, int fd);

#endif