/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/01/03 20:32:02 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

unsigned long	createhexcolour(char *line, int *i)
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
	my_mlx->light->s[0] = ft_atof_peer(line, i);
	my_mlx->light->s[1] = ft_atof_peer(line, i);
	my_mlx->light->s[2] = ft_atof_peer(line, i);
	my_mlx->light->brightness = ft_atof_peer(line, i);
	my_mlx->light->colour = createhexcolour(line, i);
	my_mlx->light->next = NULL;
	printf("Light:coords={%f, %f, %f}, brightness=%f, colour=0x%lX\n", my_mlx->light->s[0], my_mlx->light->s[1], my_mlx->light->s[2], my_mlx->light->brightness, my_mlx->light->colour);
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
	my_mlx->cam->s[0] = ft_atof_peer(line, i);
	my_mlx->cam->s[1] = ft_atof_peer(line, i);
	my_mlx->cam->s[2] = ft_atof_peer(line, i);
	my_mlx->cam->v[0] = ft_atof_peer(line, i);
	my_mlx->cam->v[1] = ft_atof_peer(line, i);
	my_mlx->cam->v[2] = ft_atof_peer(line, i);
	my_mlx->cam->fov = ft_atoi_peer(line, i);
	my_mlx->cam->radfov = my_mlx->cam->fov * (M_PI / 180);
	my_mlx->cam->next = NULL;
	if (head != NULL)
		my_mlx->cam = head;
	printf("camera: coords={%f, %f, %f}, vector={%f, %f, %f}, fov=%i, rad=%f\n", my_mlx->cam->s[0], my_mlx->cam->s[1], my_mlx->cam->s[2], my_mlx->cam->v[0], my_mlx->cam->v[1], my_mlx->cam->v[2], my_mlx->cam->fov, my_mlx->cam->radfov);
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
