/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:29:59 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:30:00 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_back_plane(t_plane **alst, t_plane *new)
{
	t_plane *tmp;

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

int		parse_plane(t_data *my_mlx, char *line, int *i)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (new == NULL)
		return (-1);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->normal.x = ft_atof_peer(line, i);
	new->normal.y = ft_atof_peer(line, i);
	new->normal.y *= -1;
	new->normal.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->normal) != 0)
		new->normal = vec3_normalize(new->normal);
	new->colour = parse_tcol(line, i);
	if (colour_check(new->colour) == 0 || vec3_sqr(new->normal) == 0 ||
	new->normal.x != new->normal.x || new->normal.y != new->normal.y ||
	new->normal.z != new->normal.z)
	{
		free(new);
		return (-1);
	}
	new->next = NULL;
	ft_lstadd_back_plane(&my_mlx->plane, new);
	return (1);
}
