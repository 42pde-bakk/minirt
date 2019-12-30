/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/30 17:43:49 by pde-bakk      ########   odam.nl         */
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
	my_mlx->light->x = ft_atof_peer(line, i);
	my_mlx->light->y = ft_atof_peer(line, i);
	my_mlx->light->z = ft_atof_peer(line, i);
	my_mlx->light->brightness = ft_atof_peer(line, i);
	my_mlx->light->colour = createhexcolour(line, i);
	printf("Light:coords={%f, %f, %f}, brightness=%f, colour=0x%lX\n", my_mlx->light->x, my_mlx->light->y, my_mlx->light->z, my_mlx->light->brightness, my_mlx->light->colour);
	return (1);
}

int				find_camera(t_data *my_mlx, char *line, int *i)
{
	my_mlx->cam->x = ft_atof_peer(line, i);
	my_mlx->cam->y = ft_atof_peer(line, i);
	my_mlx->cam->z = ft_atof_peer(line, i);
	my_mlx->cam->xvector = ft_atof_peer(line, i);
	my_mlx->cam->yvector = ft_atof_peer(line, i);
	my_mlx->cam->zvector = ft_atof_peer(line, i);
	my_mlx->cam->fov = ft_atoi_peer(line, i);
	printf("camera: coords={%f, %f, %f}, vector={%f, %f, %f}, fov=%i\n", my_mlx->cam->x, my_mlx->cam->y, my_mlx->cam->z, my_mlx->cam->xvector, my_mlx->cam->yvector, my_mlx->cam->zvector, my_mlx->cam->fov);
	return (1);
}

int				find_res_amb_cam_light(t_data *my_mlx, char *line, int *i)
{
	if (ft_strncmp(line, "R", 1) == 0)
	{
		my_mlx->scene->width = ft_atoi_peer(line, i);
		my_mlx->scene->height = ft_atoi_peer(line, i);
		printf("Resolution= W%i by H%i\n", my_mlx->scene->width, my_mlx->scene->height);
		return (1);
	}
	else if (ft_strncmp(line, "A", 2) == 0)
	{
		my_mlx->scene->amblight = ft_atof_peer(line, i);
		my_mlx->scene->amblightcolor = createhexcolour(line, i);
		printf("Ambient lighting: %f, color=%X\n", my_mlx->scene->amblight, my_mlx->scene->amblightcolor);
		return (1);
	}
	else if (ft_strncmp(line, "c", 2) == 0)
		return (find_camera(my_mlx, line, i));
	else if (ft_strncmp(line, "l", 2) == 0)
		return (find_light(my_mlx, line, i));
	else
		return (0);
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
//		start = i;
//		while (ft_isalpha(line[i]) == 1)
//			i++;
//		my_mlx->scene->id = ft_substr(line, start, i - start);
//		while (ft_iswhitespace(line[i]) == 1)
//			i++;
		if (find_res_amb_cam_light(my_mlx, line, &i) == 0)
			if (ft_objectcheck(my_mlx->scene->id) > 0)
				return ;
		free(line);
//		free(my_mlx->scene->id);
	}
}
