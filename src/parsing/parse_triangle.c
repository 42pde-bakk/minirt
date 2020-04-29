/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_triangle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:29:52 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:29:53 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_lstadd_back_triangle(t_triangle **alst, t_triangle *new)
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

int			isequal(t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
		return (1);
	if (p1.x == p3.x && p1.y == p3.y && p1.z == p3.z)
		return (1);
	if (p2.x == p3.x && p2.y == p3.y && p2.z == p3.z)
		return (1);
	return (0);
}

t_triangle	*create_back_triangle(t_triangle *front)
{
	t_triangle	*back;

	back = malloc(sizeof(t_square));
	if (back == NULL)
		return (NULL);
	back->colour = front->colour;
	back->normal = vec3_neg(front->normal);
	back->s0 = vec3_sub(front->s2, vec3_mult(back->normal, 2 * EPSILON));
	back->s1 = vec3_sub(front->s1, vec3_mult(back->normal, 2 * EPSILON));
	back->s2 = vec3_sub(front->s0, vec3_mult(back->normal, 2 * EPSILON));
	back->next = NULL;
	return (back);
}

void		parse_triangle_from_file(t_triangle *new, char *line, int *i)
{
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
}

int			parse_triangle(t_data *my_mlx, char *line, int *i)
{
	t_triangle	*new;
	t_triangle	*back;

	new = malloc(sizeof(t_triangle));
	if (new == NULL)
		return (-1);
	parse_triangle_from_file(new, line, i);
	if (colour_check(new->colour) == 0 ||
		isequal(new->s0, new->s1, new->s2) == 1)
	{
		free(new);
		return (-1);
	}
	new->normal = crossproduct(vec3_sub(new->s1, new->s0),
				vec3_sub(new->s2, new->s0));
	new->normal = vec3_normalize(new->normal);
	new->next = NULL;
	ft_lstadd_back_triangle(&my_mlx->triangle, new);
	back = create_back_triangle(new);
	if (back == NULL)
		return (-1);
	ft_lstadd_back_triangle(&my_mlx->triangle, back);
	return (1);
}
