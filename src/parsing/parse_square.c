/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_square.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:03:11 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 21:49:15 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_square(t_square **alst, t_square *new)
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

int		parse_square_2(t_square *new)
{
	new->localmat = mat4_lookat(new->s, vec3_add(new->s, new->normal));
	new->upvec = vec3_mult(new->localmat.up, new->size / 2);
	new->rightvec = vec3_mult(new->localmat.r, new->size / 2);
	new->tri[0].s0 = vec3_sub(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[0].s1 = vec3_add(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[0].s2 = vec3_sub(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[1].s0 = vec3_add(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[1].s1 = new->tri[0].s1;
	new->tri[1].s2 = new->tri[0].s2;
	new->tri[0].colour = new->colour;
	new->tri[1].colour = new->colour;
	return (1);
}

int		parse_square(t_data *my_mlx, char *line, int *i)
{
	t_square	*new;

	new = malloc(sizeof(t_square));
	if (new == NULL)
		return (-1);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.y *= -1;
	new->normal.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->normal) == 0)
		new->normal.z = 1.0;
	new->normal = vec3_normalize(new->normal);
	new->size = fmax(0.0, ft_atof_peer(line, i));
	new->colour = parse_tcol(line, i);
	new->next = NULL;
	parse_square_2(new);
	ft_lstadd_back_square(&my_mlx->square, new);
	return (1);
}
