/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/31 19:25:57 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	parse_tcol(char *line, int *i)
{
	t_col	new;

	new.r = fmax(0.0, fmin(255.0, ft_atof_peer(line, i)));
	new.g = fmax(0.0, fmin(255.0, ft_atof_peer(line, i)));
	new.b = fmax(0.0, fmin(255.0, ft_atof_peer(line, i)));
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

int		find_res_amb_cam_light(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "R ", 2) == 0)
	{
		my_mlx->scene->width = fmax(0.0,
		fmin(MAX_RESX, ft_atof_peer(line, i)));
		my_mlx->scene->height = fmax(0.0,
		fmin(MAX_RESY, ft_atof_peer(line, i)));
		return (1);
	}
	else if (ft_strncmp(line, "A ", 2) == 0)
	{
		my_mlx->scene->ambintensity = fmax(0.0, fmin(1.0,
		ft_atof_peer(line, i)));
		my_mlx->scene->amblightcolour = parse_tcol(line, i);
		return (1);
	}
	else if (ft_strncmp(line, "c ", 2) == 0)
		return (parse_camera(my_mlx, line, i));
	else if (ft_strncmp(line, "l ", 2) == 0)
		return (parse_light(my_mlx, line, i));
	else
		return (parse_objects(my_mlx, line, i));
}

void	ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		start;
	int		i;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
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
