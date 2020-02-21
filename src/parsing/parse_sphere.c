/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 22:06:16 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/21 20:20:31 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_sphere(t_sphere **alst, t_sphere *new)
{
	t_sphere *tmp;

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

int		parse_sphere(t_data *my_mlx, char *line, int *i)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (new == NULL)
		return (-1);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->diameter = ft_atof_peer(line, i);
	new->colour = parse_tcol(line, i);
	if (colour_check(new->colour) == 0 || new->diameter < 0.0)
	{
		free(new);
		return (-1);
	}
	new->next = NULL;
	ft_lstadd_back_sphere(&my_mlx->sphere, new);
	return (1);
}
