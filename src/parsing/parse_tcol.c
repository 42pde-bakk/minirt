/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_tcol.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:39:29 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/18 16:07:40 by peerdb        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	parse_tcol(char *line, int *i)
{
	t_col	new;

	new = (t_col){-1.0, -1.0, -1.0};
	new.r = ft_atof_peer(line, i);
	if (line[*i] != ',')
		return (new);
	else
		(*i)++;
	new.g = ft_atof_peer(line, i);
	if (line[*i] != ',')
		return (new);
	else
		(*i)++;
	if (line[*i] == 0)
		return (new);
	new.b = ft_atof_peer(line, i);
	return (new);
}
