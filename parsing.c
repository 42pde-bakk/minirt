/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/17 23:39:06 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

t_col			parse_tcol(char *line, int *i)
{
	t_col	new;

	new.r = ft_atof_peer(line, i);
	new.g = ft_atof_peer(line, i);
	new.b = ft_atof_peer(line, i);
	return (new);
}

void			ft_lstadd_back_light(t_light **alst, t_light *new)
{
	t_light *tmp;

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

int				find_light(t_data *my_mlx, char *line, int *i)
{
	t_light *new;

	new = malloc(sizeof(t_light));
	if (new == NULL)
		return (0);
	new->s.x = ft_atof_peer(line, i);
	new->s.y = ft_atof_peer(line, i);
	new->s.z = ft_atof_peer(line, i);

	new->brightness = fmax(0.0, fmin(1.0, ft_atof_peer(line, i)));
	new->colour = parse_tcol(line, i);
	new->next = NULL;
	ft_lstadd_back_light(&my_mlx->light, new);
	printf("Light:coords={%f, %f, %f}, brightness=%f, colour={%f, %f, %f}\n", new->s.x, new->s.y, new->s.z, new->brightness, new->colour.r, new->colour.g, new->colour.b);
	return (1);
}

int				find_camera(t_data *my_mlx, char *line, int *i)
{
	t_cam	*head;

	head = my_mlx->cam;
	while (my_mlx->cam != NULL)
		my_mlx->cam = my_mlx->cam->next;
	my_mlx->cam = malloc(sizeof(t_cam));
	if (!my_mlx->cam)
		return (0);
	my_mlx->cam->s.x = ft_atof_peer(line, i);
	my_mlx->cam->s.y = ft_atof_peer(line, i);
	my_mlx->cam->s.z = ft_atof_peer(line, i);

	my_mlx->cam->v.x = ft_atof_peer(line, i);
	my_mlx->cam->v.y = ft_atof_peer(line, i);
	my_mlx->cam->v.z = ft_atof_peer(line, i);

	my_mlx->cam->fov = ft_atoi_peer(line, i);
	my_mlx->cam->next = NULL;
	if (head != NULL)
		my_mlx->cam = head;
	printf("camera: coords={%f, %f, %f}, vector={%f, %f, %f}, fov=%i\n", my_mlx->cam->s.x, my_mlx->cam->s.y, my_mlx->cam->s.z, my_mlx->cam->v.x, my_mlx->cam->v.y, my_mlx->cam->v.z, my_mlx->cam->fov);
	return (1);
}

int				find_res_amb_cam_light(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "R ", 2) == 0)
	{
		my_mlx->scene->width = fmin(2560.0, ft_atof_peer(line, i));
		my_mlx->scene->height = fmin(1440.0, ft_atof_peer(line, i));
		printf("Resolution= W%f by H%f\n", my_mlx->scene->width, my_mlx->scene->height);
		printf("Max_res=[%i, %i]\n", MAX_RESX, MAX_RESY);
		return (1);
	}
	else if (ft_strncmp(line, "A ", 2) == 0)
	{
		my_mlx->scene->ambintensity = ft_atof_peer(line, i);
		my_mlx->scene->amblightcolour = parse_tcol(line, i);
		printf("Ambient lighting: %f, color={%f, %f, %f}\n", my_mlx->scene->ambintensity, my_mlx->scene->amblightcolour.r, my_mlx->scene->amblightcolour.g, my_mlx->scene->amblightcolour.b);
		return (1);
	}
	else if (ft_strncmp(line, "c ", 2) == 0)
		return (find_camera(my_mlx, line, i));
	else if (ft_strncmp(line, "l ", 2) == 0)
		return (find_light(my_mlx, line, i));
	else
		return (parse_objects(my_mlx, line, i));
}

void			ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		start;
	int		i;

	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		start = i;
		while (ft_isalpha(line[i]) == 1)
			i++;
		my_mlx->scene->id = ft_substr(line, start, i - start);
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		find_res_amb_cam_light(my_mlx, line, &i);
		free(line);
		free(my_mlx->scene->id);
	}
	return ;
}
