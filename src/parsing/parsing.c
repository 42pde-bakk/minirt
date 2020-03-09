/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/05 17:31:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_ambient(t_data *my_mlx, char *line, int *i)
{
	static int	check = 0;

	if (check > 0)
		return (-1);
	check++;
	my_mlx->scene->ambintensity = ft_atof_peer(line, i);
	my_mlx->scene->amblightcolour = parse_tcol(line, i);
	if (between_check(my_mlx->scene->ambintensity) == 0)
		return (-1);
	if (colour_check(my_mlx->scene->amblightcolour) == 0)
		return (-1);
	return (1);
}

int		find_specifiers(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (parse_resolution(my_mlx, line, i));
	else if (ft_strncmp(line, "A ", 2) == 0)
		return (parse_ambient(my_mlx, line, i));
	else if (ft_strncmp(line, "c ", 2) == 0)
		return (parse_camera(my_mlx, line, i));
	else if (ft_strncmp(line, "l ", 2) == 0)
		return (parse_light(my_mlx, line, i));
	else if (ft_strncmp(line, "sp ", 3) == 0)
		return (parse_sphere(my_mlx, line, i));
	else if (ft_strncmp(line, "pl ", 3) == 0)
		return (parse_plane(my_mlx, line, i));
	else if (ft_strncmp(line, "sq ", 3) == 0)
		return (parse_square(my_mlx, line, i));
	else if (ft_strncmp(line, "cy ", 3) == 0)
		return (parse_cylinder(my_mlx, line, i));
	else if (ft_strncmp(line, "tr ", 3) == 0)
		return (parse_triangle(my_mlx, line, i));
	return (0);
}

int		ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		i;
	int		gnlret;
	int		parsingret;

	gnlret = 1;
	while (gnlret > 0)
	{
		gnlret = get_next_line(fd, &line);
		if (gnlret == -1)
			return (-1);
		i = 0;
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		while (ft_isalpha(line[i]) == 1)
			i++;
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		parsingret = find_specifiers(my_mlx, line, &i);
		free(line);
		if (parsingret == -1)
			return (-1);
	}
	return (1);
}
