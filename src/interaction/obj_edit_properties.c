/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_properties.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/06 01:29:43 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/06 21:31:19 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		sphere_edit_properties(t_data *my_mlx, double distx, double disty)
{
	t_sphere	*spherehead;
	int			i;

	i = 0;
	spherehead = my_mlx->sphere;
	while (i < my_mlx->click->index && my_mlx->sphere)
	{
		i++;
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere->s = vec3_sub(my_mlx->sphere->s,
	vec3_mult(my_mlx->cam->c2w.r, distx * my_mlx->click->distance
	/ my_mlx->scene->width));
	my_mlx->sphere->s = vec3_sub(my_mlx->sphere->s,
	vec3_mult(my_mlx->cam->c2w.up, disty * my_mlx->click->distance
	/ my_mlx->scene->height));
	my_mlx->sphere = spherehead;
	return (1);
}

int		triangle_edit_properties(t_data *my_mlx, double distx, double disty)
{
	t_triangle	*trianglehead;
	int			i;

	i = 0;
	trianglehead = my_mlx->triangle;
	while (i < my_mlx->click->index && my_mlx->triangle)
	{
		i++;
		my_mlx->triangle = my_mlx->triangle->next;
	}
	my_mlx->triangle->s0 = vec3_sub(my_mlx->triangle->s0, vec3_mult(
my_mlx->cam->c2w.r, distx * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s0 = vec3_sub(my_mlx->triangle->s0, vec3_mult(
my_mlx->cam->c2w.up, disty * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle->s1 = vec3_sub(my_mlx->triangle->s1, vec3_mult(
my_mlx->cam->c2w.r, distx * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s1 = vec3_sub(my_mlx->triangle->s1, vec3_mult(
my_mlx->cam->c2w.up, disty * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle->s2 = vec3_sub(my_mlx->triangle->s2, vec3_mult(
my_mlx->cam->c2w.r, distx * my_mlx->click->distance / my_mlx->scene->width));
	my_mlx->triangle->s2 = vec3_sub(my_mlx->triangle->s2, vec3_mult(
my_mlx->cam->c2w.up, disty * my_mlx->click->distance / my_mlx->scene->height));
	my_mlx->triangle = trianglehead;
	return (1);
}

int	square_edit_properties(t_data *my_mlx, double distx, double disty)
{
	t_square	*squarehead;
	int			i;

	i = 0;
	squarehead = my_mlx->square;
	while (i < my_mlx->click->index && my_mlx->square)
	{
		i++;
		my_mlx->square = my_mlx->square->next;
	}
	my_mlx->square->s = vec3_sub(my_mlx->square->s,
vec3_mult(my_mlx->cam->c2w.r, distx * my_mlx->click->distance
	/ my_mlx->scene->width));
	my_mlx->square->s = vec3_sub(my_mlx->square->s,
vec3_mult(my_mlx->cam->c2w.up, disty * my_mlx->click->distance
	/ my_mlx->scene->height));
	my_mlx->square = squarehead;
	return (1);
}

int	plane_edit_properties(t_data *my_mlx, double distx, double disty)
{
	t_plane	*planehead;
	int		i;

	i = 0;
	planehead = my_mlx->plane;
	while (i < my_mlx->click->index && my_mlx->plane)
	{
		i++;
		my_mlx->plane = my_mlx->plane->next;
	}
	my_mlx->plane->s = vec3_sub(my_mlx->plane->s,
vec3_mult(my_mlx->cam->c2w.r, distx * my_mlx->click->distance
	/ my_mlx->scene->width));
	my_mlx->plane->s = vec3_sub(my_mlx->plane->s,
vec3_mult(my_mlx->cam->c2w.up, disty * my_mlx->click->distance
	/ my_mlx->scene->height));
	my_mlx->plane = planehead;
	return (1);
}

int	cylinder_edit_properties(t_data *my_mlx, double distx, double disty)
{
	t_cylinder	*cylinderhead;
	int			i;

	i = 0;
	cylinderhead = my_mlx->cylinder;
	while (i < my_mlx->click->index && my_mlx->cylinder)
	{
		i++;
		my_mlx->cylinder = my_mlx->cylinder->next;
	}
	my_mlx->cylinder->s = vec3_sub(my_mlx->cylinder->s,
vec3_mult(my_mlx->cam->c2w.r, distx * my_mlx->click->distance
	/ my_mlx->scene->width));
	my_mlx->cylinder->s = vec3_sub(my_mlx->cylinder->s,
vec3_mult(my_mlx->cam->c2w.up, disty * my_mlx->click->distance
	/ my_mlx->scene->height));
	my_mlx->cylinder = cylinderhead;
	return (1);
}