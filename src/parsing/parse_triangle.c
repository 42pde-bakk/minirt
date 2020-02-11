/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:04:59 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/11 21:48:50 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_triangle(t_triangle **alst, t_triangle *new)
{
	t_triangle *tmp;

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

int		parse_triangle(t_data *my_mlx, char *line, int *i)
{
	t_triangle	*new;
	t_vec3		tmp1;
	t_vec3		tmp2;

	new = malloc(sizeof(t_triangle));
	if (new == NULL)
		return (-1);
	new->s0.x = ft_atof_peer(line, i);
	new->s0.y = ft_atof_peer(line, i);
	new->s0.z = ft_atof_peer(line, i);
	new->s1.x = ft_atof_peer(line, i);
	new->s1.y = ft_atof_peer(line, i);
	new->s1.z = ft_atof_peer(line, i);
	new->s2.x = ft_atof_peer(line, i);
	new->s2.y = ft_atof_peer(line, i);
	new->s2.z = ft_atof_peer(line, i);
	new->colour = parse_tcol(line, i);
	tmp1 = vec3_sub(new->s1, new->s0);
	tmp2 = vec3_sub(new->s2, new->s0);
	new->normal = crossproduct(tmp1, tmp2);
	new->normal = vec3_normalize(new->normal);
	new->next = NULL;
	ft_lstadd_back_triangle(&my_mlx->triangle, new);
	return (1);
}
