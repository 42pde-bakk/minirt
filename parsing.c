/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/29 18:55:23 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

unsigned long	createRGB(char *line, int i)
{
	int	r;
	int g;
	int b;

	i += 1;
	printf("line[%d]=%c, next=%c\n", i, line[i], line[i+1]);
	r = ft_atoi_peer(line, i);
	i += ft_amount(r) + 1;
	g = ft_atoi_peer(line, i);
	i += ft_amount(g) + 1;
	b = ft_atoi_peer(line, i);
	printf("myRGB=%i, %i, %i\n", r, g, b);
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int		ft_idfinder(t_data *my_mlx, char *line, int i)
{
	if (ft_strncmp(my_mlx->scene->id, "R", 2) == 0)
	{
		my_mlx->scene->width = ft_atoi_peer(line, i);
		i = i + ft_amount(my_mlx->scene->width) + 1;
//		printf("line[%d]=%c, next=%c\n", i, line[i], line[i+1]);
		my_mlx->scene->height = ft_atoi_peer(line, i);
		printf("Res: width=%i, height=%i\n", my_mlx->scene->width, my_mlx->scene->height);
	}
	else if (ft_strncmp(my_mlx->scene->id, "A", 2) == 0)
	{
		printf("Ambience\n");
//		while (ft_iswhitespace(line[i]) == 1)
//			i++;
		my_mlx->scene->amblight = ft_atof_peer(line, i);
//		i = i + ft_amount(my_mlx->scene->amblight);
		while (line[i] >= 46 && line[i] <= '9')
			i++;
		printf("i=%i\n", i);
		my_mlx->scene->amblightcolor = createRGB(line, i);
		printf("Amb: %f, color=%u\n", my_mlx->scene->amblight, my_mlx->scene->amblightcolor);
	}
	return (i);
}

void	ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		start;
	int		i;

	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		printf("getnextline initiated, start prepping for disaster\n");
		printf("LINE=%s\n", line);
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		start = i;
		while (ft_isalpha(line[i]) == 1)
			i++;
		my_mlx->scene->id = ft_substr(line, start, i - start);
		while (ft_iswhitespace(line[i]) == 1)
			   i++;
		if (ft_objectcheck(my_mlx->scene->id) > 0)
			return ;
		printf("line[%i]=%c, next=%c\n", i, line[i], line[i+1]);
		i = ft_idfinder(my_mlx, line, i);
		free(line);
		free(my_mlx->scene->id);
		printf("counting: i=%d\n", i);
	}
}
