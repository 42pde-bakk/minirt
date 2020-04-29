/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 22:12:23 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/04/24 18:12:35 by peer          ########   odam.nl         */
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
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

void			parse_camera_from_file(t_cam *new, char *line, int *i)
{
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);
	new->v.x = ft_atof_peer(line, i);
	new->v.y = ft_atof_peer(line, i);
	new->v.z = ft_atof_peer(line, i);
	new->v = vec3_normalize(new->v);
	new->fov = fmin(120, ft_atoi_peer(line, i));
}

int				parse_camera(t_data *my_mlx, char *line, int *i)
{
	t_cam		*new;
	static int	headcheck = 0;

	new = malloc(sizeof(t_cam));
	if (new == NULL)
		return (-1);
	parse_camera_from_file(new, line, i);
	if (new->fov < 0.0
	|| new->v.x != new->v.x || new->v.y != new->v.y || new->v.z != new->v.z)
	{
		free(new);
		return (-1);
	}
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
