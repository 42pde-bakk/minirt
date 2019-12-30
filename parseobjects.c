/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parseobjects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:04:59 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/30 19:04:16 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_sphere(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->sphere)
		my_mlx->sphere = my_mlx->sphere->next;
	my_mlx->sphere = malloc(sizeof(t_data));
	if (my_mlx->sphere == NULL)
		return (0);
	my_mlx->sphere->x = ft_atof_peer(line, i);
	my_mlx->sphere->y = ft_atof_peer(line, i);
	my_mlx->sphere->z = ft_atof_peer(line, i);
	my_mlx->sphere->diameter = ft_atof_peer(line, i);
	my_mlx->sphere->colour = createhexcolour(line, i);
	my_mlx->sphere->next = NULL;
	printf("sphere: {%f, %f, %f}, d=%f, c=%lu\n", my_mlx->sphere->x, my_mlx->sphere->y, my_mlx->sphere->z, my_mlx->sphere->diameter, my_mlx->sphere->colour);
	return (1);
}

int		parse_plane(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->plane)
		my_mlx->plane = my_mlx->plane->next;
	my_mlx->plane = malloc(sizeof(t_data));
	if (my_mlx->plane == NULL)
		return (0);
	my_mlx->plane->x = ft_atof_peer(line, i);
	my_mlx->plane->y = ft_atof_peer(line, i);
	my_mlx->plane->z = ft_atof_peer(line, i);
	my_mlx->plane->xvector = ft_atof_peer(line, i);
	my_mlx->plane->yvector = ft_atof_peer(line, i);
	my_mlx->plane->zvector = ft_atof_peer(line, i);
	my_mlx->plane->colour = createhexcolour(line, i);
	my_mlx->plane->next = NULL;
	printf("Plane parsed: {%f, %f, %f}, {%f, %f, %f}, c=%lu\n", my_mlx->plane->x, my_mlx->plane->y, my_mlx->plane->z, my_mlx->plane->xvector, my_mlx->plane->yvector, my_mlx->plane->zvector, my_mlx->plane->colour);
	return (1);
}

int		parse_square(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->square)
		my_mlx->square = my_mlx->square->next;
	my_mlx->square = malloc(sizeof(t_data));
	if (my_mlx->square == NULL)
		return (0);
	my_mlx->square->x = ft_atof_peer(line, i);
	my_mlx->square->y = ft_atof_peer(line, i);
	my_mlx->square->z = ft_atof_peer(line, i);
	my_mlx->square->xvector = ft_atof_peer(line, i);
	my_mlx->square->yvector = ft_atof_peer(line, i);
	my_mlx->square->zvector = ft_atof_peer(line, i);
	my_mlx->square->size = ft_atof_peer(line, i);
	my_mlx->square->colour = createhexcolour(line, i);
	my_mlx->square->next = NULL;
	printf("Square parsed: {%f, %f, %f}, {%f, %f, %f}, s=%f, c=%lu\n", my_mlx->square->x, my_mlx->square->y, my_mlx->square->z, my_mlx->square->xvector, my_mlx->square->yvector, my_mlx->square->zvector, my_mlx->square->size, my_mlx->square->colour);
	return (1);
}

int		parse_cylinder(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->cylinder)
		my_mlx->cylinder = my_mlx->cylinder->next;
	my_mlx->cylinder = malloc(sizeof(t_data));
	if (my_mlx->cylinder == NULL)
		return (0);
	my_mlx->cylinder->x = ft_atof_peer(line, i);
	my_mlx->cylinder->y = ft_atof_peer(line, i);
	my_mlx->cylinder->z = ft_atof_peer(line, i);
	my_mlx->cylinder->xvector = ft_atof_peer(line, i);
	my_mlx->cylinder->yvector = ft_atof_peer(line, i);
	my_mlx->cylinder->zvector = ft_atof_peer(line, i);
	my_mlx->cylinder->diameter = ft_atof_peer(line, i);
	my_mlx->cylinder->height = ft_atof_peer(line, i);
	my_mlx->cylinder->colour = createhexcolour(line, i);
	my_mlx->cylinder->next = NULL;
	printf("Cylinder parsed: {%f, %f, %f}, {%f, %f, %f}, d=%f, h=%f, c=%lu\n", my_mlx->cylinder->x, my_mlx->cylinder->y, my_mlx->cylinder->z, my_mlx->cylinder->xvector, my_mlx->cylinder->yvector, my_mlx->cylinder->zvector, my_mlx->cylinder->diameter, my_mlx->cylinder->height, my_mlx->cylinder->colour);
	return (1);
}

int		parse_triangle(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->triangle)
		my_mlx->triangle = my_mlx->triangle->next;
	my_mlx->triangle = malloc(sizeof(t_data));
	if (my_mlx->triangle == NULL)
		return (0);
	my_mlx->triangle->x1 = ft_atof_peer(line, i);
	my_mlx->triangle->y1 = ft_atof_peer(line, i);
	my_mlx->triangle->z1 = ft_atof_peer(line, i);
	my_mlx->triangle->x2 = ft_atof_peer(line, i);
	my_mlx->triangle->y2 = ft_atof_peer(line, i);
	my_mlx->triangle->z2 = ft_atof_peer(line, i);
	my_mlx->triangle->x3 = ft_atof_peer(line, i);
	my_mlx->triangle->y3 = ft_atof_peer(line, i);
	my_mlx->triangle->z3 = ft_atof_peer(line, i);
	my_mlx->triangle->colour = createhexcolour(line, i);
	my_mlx->triangle->next = NULL;
	printf("Triangle parsed: {%f, %f, %f}, {%f, %f, %f}, {%f, %f, %f}, c=%lu\n", my_mlx->triangle->x1, my_mlx->triangle->y1, my_mlx->triangle->z1, my_mlx->triangle->x2, my_mlx->triangle->y2, my_mlx->triangle->z2, my_mlx->triangle->x3, my_mlx->triangle->y3, my_mlx->triangle->z3, my_mlx->triangle->colour);
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
