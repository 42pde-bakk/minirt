/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parseobjects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:04:59 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/04 18:34:42 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_cylinder(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->cylinder)
		my_mlx->cylinder = my_mlx->cylinder->next;
	my_mlx->cylinder = malloc(sizeof(t_cylinder));
	if (my_mlx->cylinder == NULL)
		return (0);
	my_mlx->cylinder->s[0] = ft_atof_peer(line, i);
	my_mlx->cylinder->s[1] = ft_atof_peer(line, i);
	my_mlx->cylinder->s[2] = ft_atof_peer(line, i);
	my_mlx->cylinder->v[0] = ft_atof_peer(line, i);
	my_mlx->cylinder->v[1] = ft_atof_peer(line, i);
	my_mlx->cylinder->v[2] = ft_atof_peer(line, i);
	my_mlx->cylinder->diameter = ft_atof_peer(line, i);
	my_mlx->cylinder->height = ft_atof_peer(line, i);
	my_mlx->cylinder->colour = createhexcolour(line, i);
	my_mlx->cylinder->next = NULL;
	printf("Cylinder parsed: {%f, %f, %f}, {%f, %f, %f}, d=%f, h=%f, c=%#lX\n", my_mlx->cylinder->s[0], my_mlx->cylinder->s[1], my_mlx->cylinder->s[2], my_mlx->cylinder->v[0], my_mlx->cylinder->v[1], my_mlx->cylinder->v[2], my_mlx->cylinder->diameter, my_mlx->cylinder->height, my_mlx->cylinder->colour);
	return (1);
}

int		parse_triangle(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->triangle)
		my_mlx->triangle = my_mlx->triangle->next;
	my_mlx->triangle = malloc(sizeof(t_triangle));
	if (my_mlx->triangle == NULL)
		return (0);
	my_mlx->triangle->s1[0] = ft_atof_peer(line, i);
	my_mlx->triangle->s1[1] = ft_atof_peer(line, i);
	my_mlx->triangle->s1[2] = ft_atof_peer(line, i);
	my_mlx->triangle->s2[0] = ft_atof_peer(line, i);
	my_mlx->triangle->s2[1] = ft_atof_peer(line, i);
	my_mlx->triangle->s2[2] = ft_atof_peer(line, i);
	my_mlx->triangle->s3[0] = ft_atof_peer(line, i);
	my_mlx->triangle->s3[1] = ft_atof_peer(line, i);
	my_mlx->triangle->s3[2] = ft_atof_peer(line, i);
	my_mlx->triangle->colour = createhexcolour(line, i);
	my_mlx->triangle->next = NULL;
	printf("Triangle parsed: {%f, %f, %f}, {%f, %f, %f}, {%f, %f, %f}, c=%#lX\n", my_mlx->triangle->s1[0], my_mlx->triangle->s1[1], my_mlx->triangle->s1[2], my_mlx->triangle->s2[0], my_mlx->triangle->s2[1], my_mlx->triangle->s2[2], my_mlx->triangle->s3[0], my_mlx->triangle->s3[1], my_mlx->triangle->s3[2], my_mlx->triangle->colour);
	return (1);
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
