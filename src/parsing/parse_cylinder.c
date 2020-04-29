/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 17:59:11 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 18:12:37 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_cylinder(t_cylinder **alst, t_cylinder *new)
{
	t_cylinder	*tmp;

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

int		parse_cylinder(t_data *my_mlx, char *line, int *i)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (new == NULL)
		return (-1);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
	new->v.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->v) != 0)
		new->v = vec3_normalize(new->v);
	new->diameter = ft_atof_peer(line, i);
	new->height = ft_atof_peer(line, i);
	new->colour = parse_tcol(line, i);
	if (colour_check(new->colour) == 0 || new->diameter < 0.0 ||
		vec3_sqr(new->v) == 0 || new->height < 0.0)
	{
		free(new);
		return (-1);
	}
	new->next = NULL;
	ft_lstadd_back_cylinder(&my_mlx->cylinder, new);
	return (1);
}
