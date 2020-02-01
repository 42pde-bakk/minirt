/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 22:12:23 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/31 19:27:18 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ft_lstadd_back_camera(t_cam **alst, t_cam *new)
{
	t_cam *tmp;

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

int				parse_camera(t_data *my_mlx, char *line, int *i)
{
	t_cam		*new;
	static int	headcheck = 0;

	new = malloc(sizeof(t_cam));
	if (new == NULL)
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
	new->v.z = ft_atof_peer(line, i);
	if (vec3_sqr(new->v) == 0)
		new->v.z = 1.0;
	new->v = vec3_normalize(new->v);
	new->fov = fmin(180.0, fmax(30.0, ft_atoi_peer(line, i)));
	new->next = NULL;
	new->c2w = mat4_lookat(new->s, vec3_add(new->s, new->v));
	ft_lstadd_back_camera(&my_mlx->cam, new);
	if (headcheck == 0)
	{
		my_mlx->camhead = my_mlx->cam;
		headcheck++;
	}
	return (1);
}
