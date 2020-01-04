/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   planesquare.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 18:25:24 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/04 18:33:52 by pde-bakk      ########   odam.nl         */
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
//		printf("adding in front\n");
		new->next = *alst;
		*alst = new;
	}
}

int		parse_square(t_data *my_mlx, char *line, int *i)
{
	t_square  *new;

	new = malloc(sizeof(t_square));
	if (new == NULL)
		return (0);
	new->s[0] = ft_atof_peer(line, i);
	new->s[1] = ft_atof_peer(line, i);
	new->s[2] = ft_atof_peer(line, i);
	new->s[3] = 0;
	new->v[0] = ft_atof_peer(line, i);
	new->v[1] = ft_atof_peer(line, i);
	new->v[2] = ft_atof_peer(line, i);
	new->v[3] = 0;
	new->size = ft_atof_peer(line, i);
	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_square(&my_mlx->square, new);
	printf("square: {%f, %f, %f}, d=%f, c=%#lX\n", new->s[0], new->s[1], new->s[2], new->v[0], new->v[1], new->v[2], new->size, new->colour);
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
//		printf("adding in front\n");
		new->next = *alst;
		*alst = new;
	}
}

int		parse_plane(t_data *my_mlx, char *line, int *i)
{
	t_plane  *new;

	new = malloc(sizeof(t_plane));
	if (new == NULL)
		return (0);
	new->s[0] = ft_atof_peer(line, i);
	new->s[1] = ft_atof_peer(line, i);
	new->s[2] = ft_atof_peer(line, i);
	new->s[3] = 0;
	new->v[0] = ft_atof_peer(line, i);
	new->v[1] = ft_atof_peer(line, i);
	new->v[2] = ft_atof_peer(line, i);
	new->v[3] = 0;
	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_plane(&my_mlx->plane, new);
	printf("Plane: {%f, %f, %f}, d=%f, c=%#lX\n", new->s[0], new->s[1], new->s[2], new->v[0], new->v[1], new->v[2], new->colour);
	return (1);
}