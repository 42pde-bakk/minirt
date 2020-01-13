/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   planesquare.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 18:25:24 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/13 14:12:27 by Peer de Bak   ########   odam.nl         */
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

	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
//	new->v.y = new->v.y * -1;
	new->v.z = ft_atof_peer(line, i);

	new->size = ft_atof_peer(line, i);
	new->colour = createhexcolour(line, i);
	new->next = NULL;
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

	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_plane(&my_mlx->plane, new);
	printf("new plane @ {%f, %f, %f} with normal={%f, %f, %f} colour=%X\n", new->s.x, new->s.y, new->s.z, new->normal.x, new->normal.y, new->normal.z, new->colour);
	return (1);
}
