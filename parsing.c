/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/27 11:47:08 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/27 18:35:49 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "includes/gnl/get_next_line.h"

void	ft_idfinder(t_data *my_mlx, char *line, int i)
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
		my_mlx->scene->amblight = ft_atoi(line);
		i = i + ft_amount(my_mlx->scene->amblight);
	}
}

void	ft_parser(t_data *my_mlx, int fd)
{
	char	*line;
	int		start;
	int		i;

	start = 0;
	i = 0;
	printf("start parsing\n");
	while (get_next_line(fd, &line) > 0)
	{
		printf("getnextline initiated, start prepping for disaster\n");
		while (ft_iswhitespace(line[i]) == 1)
			i++;
		start = i;
		while (ft_isalpha(line[i]) == 1)
			i++;
		printf("till here and no further\n");
		my_mlx->scene->id = ft_substr(line, start, i - start + 1);
		printf("id=%s\n", my_mlx->scene->id);
		if (ft_objectcheck(my_mlx->scene->id) > 0)
			return ;
		ft_idfinder(my_mlx, line, i);
//		free(line);
		printf("counting: i=%d\n", i);
	}
}
