/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_edit_props_square.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 22:19:38 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 22:20:04 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calc_new_triangles(t_square *sq)
{
	sq->localmat = mat4_lookat(sq->s, vec3_add(sq->s, sq->normal));
	sq->upvec = vec3_mult(sq->localmat.up, sq->size / 2);
	sq->rightvec = vec3_mult(sq->localmat.r, sq->size / 2);
	sq->tri[0].s0 = vec3_sub(vec3_sub(sq->s, sq->upvec), sq->rightvec);
	sq->tri[0].s1 = vec3_add(vec3_add(sq->s, sq->upvec), sq->rightvec);
	sq->tri[0].s2 = vec3_sub(vec3_add(sq->s, sq->upvec), sq->rightvec);
	sq->tri[1].s0 = sq->tri[0].s0;
	sq->tri[1].s1 = vec3_add(vec3_sub(sq->s, sq->upvec), sq->rightvec);
	sq->tri[1].s2 = sq->tri[0].s1;
	return (1);
}

int	square_edit_back(t_data *my_mlx)
{
	t_square	*squarehead;
	int			i;

	i = 0;
	squarehead = my_mlx->square;
	if (my_mlx->click->index % 2 == 0)
		my_mlx->click->index += 1;
	else
		my_mlx->click->index -= 1;
	while (i < my_mlx->click->index && my_mlx->square)
	{
		i++;
		my_mlx->square = my_mlx->square->next;
	}
	my_mlx->square->normal = vec3_neg(my_mlx->click->rotation);
	my_mlx->square->s = obj_move(my_mlx->square->s, my_mlx);
	calc_new_triangles(my_mlx->square);
	my_mlx->square->size *= my_mlx->click->sizemult;
	my_mlx->square = squarehead;
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
	my_mlx->square->normal = my_mlx->click->rotation;
	my_mlx->square->s = obj_move(my_mlx->square->s, my_mlx);
	calc_new_triangles(my_mlx->square);
	my_mlx->square->size *= my_mlx->click->sizemult;
	my_mlx->square = squarehead;
	square_edit_back(my_mlx);
	return (1);
}
