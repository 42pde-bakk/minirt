/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/03 22:06:16 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/04 15:42:53 by pde-bakk      ########   odam.nl         */
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
	new->s[0] = ft_atof_peer(line, i);
	new->s[1] = ft_atof_peer(line, i);
	new->s[2] = ft_atof_peer(line, i);
	new->s[3] = 0;
	new->diameter = ft_atof_peer(line, i);
	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_sphere(&my_mlx->sphere, new);
	printf("sphere: {%f, %f, %f}, d=%f, c=%#lX\n", new->s[0], new->s[1], new->s[2], new->diameter, new->colour);
	return (1);
}
