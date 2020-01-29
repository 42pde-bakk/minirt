/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 17:59:11 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/28 20:13:35 by pde-bakk      ########   odam.nl         */
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
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
	new->v.z = ft_atof_peer(line, i);

	new->diameter = ft_atof_peer(line, i);
	new->height = ft_atof_peer(line, i);

	new->colour = parse_tcol(line, i);
	new->next = NULL;
	ft_lstadd_back_cylinder(&my_mlx->cylinder, new);
//	printf("cylinder: pos={%f, %f, %f}, v={%f, %f, %f}, diam=%f, height=%f\n", new->s.x, new->s.y, new->s.z, new->v.x, new->v.y, new->v.z, new->diameter, new->height);
	return (1);
}
