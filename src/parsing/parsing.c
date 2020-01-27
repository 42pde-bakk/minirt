/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:24:02 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col			parse_tcol(char *line, int *i)
{
	t_col	new;

	new.r = ft_atof_peer(line, i);
	new.g = ft_atof_peer(line, i);
	new.b = ft_atof_peer(line, i);
	return (new);
}

int		parse_objects(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sphere(my_mlx, line, i));
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_plane(my_mlx, line, i));
	else if (ft_strncmp(line, "sq", 2) == 0)
		return (parse_square(my_mlx, line, i));
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cylinder(my_mlx, line, i));
	else if (ft_strncmp(line, "tr", 2) == 0)
		return (parse_triangle(my_mlx, line, i));
	else
		return (0);
}

int				find_res_amb_cam_light(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "R ", 2) == 0)
	{
		my_mlx->scene->width = fmin(2560.0, ft_atof_peer(line, i));
		my_mlx->scene->height = fmin(1440.0, ft_atof_peer(line, i));
		printf("Resolution= W%f by H%f\n", my_mlx->scene->width, my_mlx->scene->height);
		printf("Max_res=[%i, %i]\n", MAX_RESX, MAX_RESY);
		return (1);
	}
	else if (ft_strncmp(line, "A ", 2) == 0)
	{
		my_mlx->scene->ambintensity = ft_atof_peer(line, i);
		my_mlx->scene->amblightcolour = parse_tcol(line, i);
		printf("Ambient lighting: %f, color={%f, %f, %f}\n", my_mlx->scene->ambintensity, my_mlx->scene->amblightcolour.r, my_mlx->scene->amblightcolour.g, my_mlx->scene->amblightcolour.b);
		return (1);
	}
	else if (ft_strncmp(line, "c ", 2) == 0)
		return (parse_camera(my_mlx, line, i));
	else if (ft_strncmp(line, "l ", 2) == 0)
		return (parse_light(my_mlx, line, i));
	else
		return (parse_objects(my_mlx, line, i));
}

void			ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		start;
	int		i;

	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		start = i;
		while (ft_isalpha(line[i]) == 1)
			i++;
		my_mlx->scene->id = ft_substr(line, start, i - start);
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		find_res_amb_cam_light(my_mlx, line, &i);
		free(line);
		free(my_mlx->scene->id);
	}
	return ;
}
