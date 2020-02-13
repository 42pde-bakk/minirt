/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_props2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 16:37:09 by Peer de Bak    #+#    #+#                */
/*   Updated: 2020/02/13 10:05:09 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cylinder_edit_properties(t_data *my_mlx)
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
	my_mlx->cylinder->s = obj_move(my_mlx->cylinder->s, my_mlx);
	my_mlx->cylinder->height *= my_mlx->click->heightmult;
	my_mlx->cylinder->diameter *= my_mlx->click->sizemult;
	my_mlx->cylinder = cylinderhead;
	return (1);
}

int	sphere_edit_properties(t_data *my_mlx)
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
	my_mlx->sphere->s = obj_move(my_mlx->sphere->s, my_mlx);
	my_mlx->sphere->diameter *= my_mlx->click->sizemult;
	my_mlx->sphere = spherehead;
	return (1);
}

int	triangle_edit_properties(t_data *my_mlx)
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
	my_mlx->triangle->s0 = obj_move(my_mlx->triangle->s0, my_mlx);
	my_mlx->triangle->s1 = obj_move(my_mlx->triangle->s1, my_mlx);
	my_mlx->triangle->s2 = obj_move(my_mlx->triangle->s2, my_mlx);
	my_mlx->triangle = trianglehead;
	return (1);
}

int	calc_new_triangles(t_square *sq)
{
	sq->localmat = mat4_lookat(sq->s, vec3_add(sq->s, sq->normal));
	sq->upvec = vec3_mult(sq->localmat.up, sq->size / 2);
	sq->rightvec = vec3_mult(sq->localmat.r, sq->size / 2);
	sq->tri[0].s0 = vec3_sub(vec3_add(sq->s, sq->upvec), sq->rightvec);
	sq->tri[0].s1 = vec3_add(vec3_add(sq->s, sq->upvec), sq->rightvec);
	sq->tri[0].s2 = vec3_sub(vec3_sub(sq->s, sq->upvec), sq->rightvec);
	sq->tri[1].s0 = vec3_add(vec3_sub(sq->s, sq->upvec), sq->rightvec);
	sq->tri[1].s1 = sq->tri[0].s1;
	sq->tri[1].s2 = sq->tri[0].s2;
	return (1);
}

int	square_edit_properties(t_data *my_mlx)
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
	my_mlx->square->s = obj_move(my_mlx->square->s, my_mlx);
	calc_new_triangles(my_mlx->square);
	my_mlx->square->size *= my_mlx->click->sizemult;
	my_mlx->square->normal = my_mlx->click->rotation;
	my_mlx->square = squarehead;
	return (1);
}

int	plane_edit_properties(t_data *my_mlx)
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
	my_mlx->plane->s = obj_move(my_mlx->plane->s, my_mlx);
	my_mlx->plane = planehead;
	return (1);
}
