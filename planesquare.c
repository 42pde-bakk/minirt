/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   planesquare.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 18:25:24 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/22 21:25:57 by pde-bakk      ########   odam.nl         */
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

int		parse_square(t_data *my_mlx, char *line, int *i)
{
	t_square	*new;

	new = malloc(sizeof(t_square));
	if (new == NULL)
		return (0);

	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.z = ft_atof_peer(line, i);
	new->size = ft_atof_peer(line, i);
	new->colour = parse_tcol(line, i);
	new->next = NULL;
	new->localmat = mat4_lookat(new->s, vec3_add(new->s, new->normal));
	new->normal.y = new->normal.y * -1;
	printmatrix(new->localmat);
	new->upvec = vec3_mult(new->localmat.up, new->size / 2);
	new->rightvec = vec3_mult(new->localmat.r, new->size / 2);
	new->tri[0].s0 = vec3_sub(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[0].s1 = vec3_sub(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[0].s2 = vec3_add(vec3_sub(new->s, new->upvec), new->rightvec);
	new->tri[0].colour = new->colour;
	new->tri[1].s2 = new->tri[0].s0;
	new->tri[1].s1 = vec3_add(vec3_add(new->s, new->upvec), new->rightvec);
	new->tri[1].s0 = new->tri[0].s2;
	new->tri[1].colour = new->colour;

	printvec(new->s, "square location");
	printvec(new->tri[0].s0, "tri[0].s0");
	printvec(new->tri[0].s1, "tri[0].s1");
	printvec(new->tri[0].s2, "tri[0].s2");
	printvec(new->tri[1].s0, "tri[1].s0");
	printvec(new->tri[1].s1, "tri[1].s1");
	printvec(new->tri[1].s2, "tri[1].s2");

	ft_lstadd_back_square(&my_mlx->square, new);
	return (1);
}

void	ft_lstadd_back_plane(t_plane **alst, t_plane *new)
{
	t_plane *tmp;

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

int		parse_plane(t_data *my_mlx, char *line, int *i)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (new == NULL)
		return (0);

	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.y *= -1;
	new->normal.z = ft_atof_peer(line, i);

	new->colour = parse_tcol(line, i);
	new->next = NULL;
	ft_lstadd_back_plane(&my_mlx->plane, new);
//	printf("new plane @ {%f, %f, %f} with normal={%f, %f, %f} colour=%{%f, %f, %f}\n", new->s.x, new->s.y, new->s.z, new->normal.x, new->normal.y, new->normal.z, new->colour.r, new->colour.g, new->colour.b);
	return (1);
}
