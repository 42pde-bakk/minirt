/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/29 16:09:11 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

int		ft_idfinder(t_data *my_mlx, char *line, int i)
{
	int		start;

	start = i;
	if (ft_strncmp(my_mlx->scene->id, "R", 2) == 0)
	{
		printf("Resolution found, maffaka\n");
		while (ft_iswhitespace(line[i]) == 1)
			   i++;
		my_mlx->scene->width = ft_atoi(line);
		i = i + ft_amount(my_mlx->scene->width);
		while (ft_iswhitespace(line[i]) == 1)
			   i++;
		my_mlx->scene->height = ft_atoi(line);
		i = i + ft_amount(my_mlx->scene->height);
	}
	if (ft_strncmp(my_mlx->scene->id, "A", 2) == 0)
	{
		printf("Ambience\n");
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		my_mlx->scene->amblight = ft_atof(line, i );
		i = i + ft_amount(my_mlx->scene->amblight);
		printf("Amb: %f, \n", my_mlx->scene->amblight);
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
		start = 0;
		i = 0;
		printf("getnextline initiated, start prepping for disaster\n");
		printf("LINE=%s\n", line);
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		start = i;
		while (ft_isalpha(line[i]) == 1)
			i++;
		my_mlx->scene->id = ft_substr(line, start, i - start);
		if (ft_objectcheck(my_mlx->scene->id) > 0)
			return ;
		i = ft_idfinder(my_mlx, line, i);
		free(line);
		free(my_mlx->scene->id);
		printf("counting: i=%d\n", i);
	}
}
