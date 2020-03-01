/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argstructs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/01 16:11:40 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/01 16:12:09 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_arg	*new_argstruct(t_data *my_mlx, int i)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
	{
		ft_putstr_fd("Error\nMalloc for argstruct failed\n", 2);
		freemachine(my_mlx);
	}
	new->my_mlx = my_mlx;
	new->threadnr = i;
	return (new);
}

void	freeargstructs(t_arg *arg[THREADCOUNT])
{
	int i;

	i = 0;
	while (i < THREADCOUNT)
	{
		free(arg[i]);
		i++;
	}
}