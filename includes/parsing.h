/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:15:30 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:15:31 by peer          ########   odam.nl         */
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
