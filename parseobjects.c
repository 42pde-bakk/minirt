/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parseobjects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:04:59 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/09 19:33:50 by Peer de Bak   ########   odam.nl         */
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

	new->colour = createhexcolour(line, i);
	new->next = NULL;
	ft_lstadd_back_cylinder(&my_mlx->cylinder, new);
	return (1);
}

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
	t_vec3	tmp1;
	t_vec3	tmp2;

	new = malloc(sizeof(t_triangle));
	if (new == NULL)
		return (0);
	new->s0.x = ft_atof_peer(line, i);
	new->s0.y = ft_atof_peer(line, i);
	new->s0.z = ft_atof_peer(line, i);

	new->s1.x = ft_atof_peer(line, i);
	new->s1.y = ft_atof_peer(line, i);
	new->s1.z = ft_atof_peer(line, i);

	new->s2.x = ft_atof_peer(line, i);
	new->s2.y = ft_atof_peer(line, i);
	new->s2.z = ft_atof_peer(line, i);

	new->colour = createhexcolour(line, i);
	tmp1 = vector_sub(new->s1, new->s0);
	tmp2 = vector_sub(new->s2, new->s0);
	new->cross = crossproduct(tmp1, tmp2);
	new->next = NULL;
	ft_lstadd_back_triangle(&my_mlx->triangle, new);
	return (1);
}

int		parse_objects(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sphere(my_mlx, line, i));
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_plane(my_mlx, line, i));
	else if (ft_strncmp(line, "sq", 2) == 0)
		return (parse_square(my_mlx, line, i));
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cylinder(my_mlx, line, i));
	else if (ft_strncmp(line, "tr", 2) == 0)
		return (parse_triangle(my_mlx, line, i));
	else
		return (0);
}
