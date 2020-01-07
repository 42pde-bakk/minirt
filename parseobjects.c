/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parseobjects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 18:04:59 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/07 19:56:10 by pde-bakk      ########   odam.nl         */
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

	new = malloc(sizeof(t_square));
	if (new == NULL)
		return (0);
	new->s[0] = ft_atof_peer(line, i);
	new->s[1] = ft_atof_peer(line, i);
	new->s[2] = ft_atof_peer(line, i);
	new->s[3] = 0;
	new->v[0] = ft_atof_peer(line, i);
	new->v[1] = ft_atof_peer(line, i);
	new->v[2] = ft_atof_peer(line, i);
	new->v[3] = 0;
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

	new = malloc(sizeof(t_triangle));
	if (new == NULL)
		return (0);
	new->s1[0] = ft_atof_peer(line, i);
	new->s1[1] = ft_atof_peer(line, i);
	new->s1[2] = ft_atof_peer(line, i);
	new->s1[3] = 0;
	new->s2[0] = ft_atof_peer(line, i);
	new->s2[1] = ft_atof_peer(line, i);
	new->s2[2] = ft_atof_peer(line, i);
	new->s2[3] = 0;
	new->s3[0] = ft_atof_peer(line, i);
	new->s3[1] = ft_atof_peer(line, i);
	new->s3[2] = ft_atof_peer(line, i);
	new->s3[3] = 0;
	new->colour = createhexcolour(line, i);
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
