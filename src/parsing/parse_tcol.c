/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tcol.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:39:29 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/05 13:39:41 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	parse_tcol(char *line, int *i)
{
	t_col	new;

	new.r = ft_atof_peer(line, i);
	new.g = ft_atof_peer(line, i);
	new.b = ft_atof_peer(line, i);
	return (new);
}
