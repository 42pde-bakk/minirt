/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 22:06:16 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/09 15:34:54 by Peer de Bak   ########   odam.nl         */
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
//		printf("adding in front\n");
		new->next = *alst;
		*alst = new;
	}
}

void	loopspheres(t_data *my_mlx)
{
	t_sphere	*head;

	head = my_mlx->sphere;
	while (my_mlx->sphere)
	{
		printf("sphere met diameter=%f\n", my_mlx->sphere->diameter);
		my_mlx->sphere = my_mlx->sphere->next;
	}
	my_mlx->sphere = head;
	printf("HEAD=sphere met diameter=%f\n", my_mlx->sphere->diameter);
}

int		parse_sphere(t_data *my_mlx, char *line, int *i)
{
	t_sphere  *new;

	new = malloc(sizeof(t_sphere));
	if (new == NULL)
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->diameter = ft_atof_peer(line, i);
	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_sphere(&my_mlx->sphere, new);
	printf("new sphere @ {%f, %f, %f} with diameter=%f\n", new->s.x, new->s.y, new->s.z, new->diameter);
	return (1);
}
