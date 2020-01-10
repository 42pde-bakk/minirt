/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/09 19:41:28 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

unsigned		createhexcolour(char *line, int *i)
{
	int	r;
	int g;
	int b;

	(*i) += 1;
	r = ft_atoi_peer(line, i);
	g = ft_atoi_peer(line, i);
	b = ft_atoi_peer(line, i);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int				find_light(t_data *my_mlx, char *line, int *i)
{
	while (my_mlx->light)
		my_mlx->light = my_mlx->light->next;
	my_mlx->light = malloc(sizeof(t_light));
	if (my_mlx->light == NULL)
		return (0);
	my_mlx->light->s.x = ft_atof_peer(line, i);
	my_mlx->light->s.y = ft_atof_peer(line, i);
	my_mlx->light->s.z = ft_atof_peer(line, i);

	my_mlx->light->brightness = ft_atof_peer(line, i);
	my_mlx->light->colour = createhexcolour(line, i);
	my_mlx->light->next = NULL;
	printf("Light:coords={%f, %f, %f}, brightness=%f, colour=0x%X\n", my_mlx->light->s.x, my_mlx->light->s.y, my_mlx->light->s.z, my_mlx->light->brightness, my_mlx->light->colour);
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
		my_mlx->scene->width = ft_atof_peer(line, i);
		my_mlx->scene->height = ft_atof_peer(line, i);
		printf("Resolution= W%f by H%f\n", my_mlx->scene->width, my_mlx->scene->height);
		return (1);
	}
	else if (ft_strncmp(line, "A ", 2) == 0)
	{
		my_mlx->scene->amblight = ft_atof_peer(line, i);
		my_mlx->scene->amblightcolor = createhexcolour(line, i);
		printf("Ambient lighting: %f, color=%X\n", my_mlx->scene->amblight, my_mlx->scene->amblightcolor);
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
