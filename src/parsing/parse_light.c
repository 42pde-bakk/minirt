/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:01:48 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/27 18:22:39 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ft_lstadd_back_light(t_light **alst, t_light *new)
{
	t_light *tmp;

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

int				parse_light(t_data *my_mlx, char *line, int *i)
{
	t_light *new;

	new = malloc(sizeof(t_light));
	if (new == NULL)
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->brightness = fmax(0.0, fmin(1.0, ft_atof_peer(line, i)));
	new->colour = parse_tcol(line, i);
	new->next = NULL;
	ft_lstadd_back_light(&my_mlx->light, new);
	printf("Light:coords={%f, %f, %f}, brightness=%f, colour={%f, %f, %f}\n", new->s.x, new->s.y, new->s.z, new->brightness, new->colour.r, new->colour.g, new->colour.b);
	return (1);
}
