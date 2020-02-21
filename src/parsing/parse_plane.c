/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/04 18:25:24 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/20 20:11:58 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return (-1);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.y *= -1;
	new->normal.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->normal) != 0)
		new->normal = vec3_normalize(new->normal);
	new->colour = parse_tcol(line, i);
	if (colour_check(new->colour) == 0 || vec3_sqr(new->normal) == 0)
	{
		free(new);
		return (-1);
	}
	new->next = NULL;
	ft_lstadd_back_plane(&my_mlx->plane, new);
	return (1);
}
