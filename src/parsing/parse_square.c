/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_square.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:03:11 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 20:18:49 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_lstadd_back_square(t_square **alst, t_square *new)
{
	t_square *tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

int			parse_square_2(t_square *new)
{
	new->localmat = mat4_lookat(new->s, vec3_add(new->s, new->normal));
	new->upvec = vec3_mult(new->localmat.up, new->size / 2);
	new->rightvec = vec3_mult(new->localmat.r, new->size / 2);
	new->tri[0].s0 = vec3_sub(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[0].s1 = vec3_add(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[0].s2 = vec3_sub(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[1].s0 = new->tri[0].s0;
	new->tri[1].s1 = vec3_add(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[1].s2 = new->tri[0].s1;
	new->tri[0].colour = new->colour;
	new->tri[1].colour = new->colour;
	new->tri[0].normal = new->normal;
	new->tri[1].normal = new->normal;
	return (1);
}

t_square	*create_backsquare(t_square *front)
{
	t_square	*back;

	back = malloc(sizeof(t_square));
	if (back == NULL)
		return (NULL);
	back->s = vec3_sub(front->s, vec3_mult(front->normal, 10.0 * EPSILON));
	back->normal = vec3_neg(front->normal);
	back->localmat = mat4_lookat(back->s, vec3_add(back->s, back->normal));
	back->size = front->size;
	back->upvec = vec3_mult(back->localmat.up, back->size / 2);
	back->rightvec = vec3_mult(back->localmat.r, back->size / 2);
	back->tri[0].s0 = vec3_sub(vec3_sub(back->s, back->upvec), back->rightvec);
	back->tri[0].s1 = vec3_add(vec3_add(back->s, back->upvec), back->rightvec);
	back->tri[0].s2 = vec3_sub(vec3_add(back->s, back->upvec), back->rightvec);
	back->tri[1].s0 = back->tri[0].s0;
	back->tri[1].s1 = vec3_add(vec3_sub(back->s, back->upvec), back->rightvec);
	back->tri[1].s2 = back->tri[0].s1;
	back->tri[0].colour = front->colour;
	back->tri[0].normal = back->normal;
	back->tri[1].colour = front->colour;
	back->tri[1].normal = back->normal;
	back->tri[0].next = NULL;
	back->tri[1].next = NULL;
	back->next = NULL;
	return (back);
}

void		parse_square_from_file(t_square *new, char *line, int *i)
{
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->normal) != 0)
		new->normal = vec3_normalize(new->normal);
	new->size = ft_atof_peer(line, i);
	new->colour = parse_tcol(line, i);
}

int			parse_square(t_data *my_mlx, char *line, int *i)
{
	t_square	*new;
	t_square	*back;

	new = malloc(sizeof(t_square));
	if (new == NULL)
		return (-1);
	parse_square_from_file(new, line, i);
	if (colour_check(new->colour) == 0 || new->size < 0.0 ||
	vec3_sqr(new->normal) == 0)
	{
		free(new);
		return (-1);
	}
	new->next = NULL;
	parse_square_2(new);
	ft_lstadd_back_square(&my_mlx->square, new);
	back = create_backsquare(new);
	if (back == NULL)
		return (-1);
	ft_lstadd_back_square(&my_mlx->square, back);
	return (1);
}
