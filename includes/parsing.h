/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 16:47:11 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/03/05 18:48:14 by pde-bakk      ########   odam.nl         */
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
int		parse_resolution(t_data *my_mlx, char *line, int *i);
int		parse_ambient(t_data *my_mlx, char *line, int *i);
int		find_specifiers(t_data *my_mlx, char *line, int *i);
int		ft_parser(t_data *my_mlx, int fd);

#endif
