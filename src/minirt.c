/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/12 18:38:22 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	data_initvalues(t_data *my_mlx)
{
	my_mlx->ray->length = __INT_MAX__;
	my_mlx->light = NULL;
	my_mlx->cam = NULL;
	my_mlx->sphere = NULL;
	my_mlx->plane = NULL;
	my_mlx->square = NULL;
	my_mlx->cylinder = NULL;
	my_mlx->triangle = NULL;
	my_mlx->frame = 1;
	my_mlx->click->state = 0;
}

int		init_my_mlx(t_data *my_mlx, int fd)
{
	my_mlx->mlx_ptr = mlx_init();
	my_mlx->scene = malloc(sizeof(t_scene));
	if (my_mlx->scene == NULL)
		return (-1);
	my_mlx->ray = malloc(sizeof(t_ray));
	if (my_mlx->ray == NULL)
		return (-1);
	my_mlx->click = malloc(sizeof(t_click));
	if (my_mlx->click == NULL)
		return (-1);
	data_initvalues(my_mlx);
	if (ft_parser(my_mlx, fd) == -1)
		return (-1);
	my_mlx->win_ptr = mlx_new_window(my_mlx->mlx_ptr, my_mlx->scene->width,
	my_mlx->scene->height, "MiniPeeRT");
	my_mlx->mlx_img = mlx_new_image(my_mlx->mlx_ptr, 1, 1);
	my_mlx->mlx_img2 = mlx_new_image(my_mlx->mlx_ptr, 1, 1);
	return (1);
}

int		argcheck(int argc, char **argv)
{
	int ret;

	ret = 0;
	if (argc < 2 || argc > 3)
		return (-1);
	if (argc == 2 || argc == 3)
	{
		ret = 1;
		if (ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) == 0)
			return (-1);
		if (argc == 3)
		{
			ret = 2;
			if (ft_strncmp(argv[1], "--save", 6) != 0)
				return (-1);
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_data	*my_mlx;

	if (argcheck(argc, argv) == -1)
	{
		write(2, "Error\nBruh...\n", ft_strlen("Error\nBruh...\n"));
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	my_mlx = malloc(sizeof(t_data));
	if (my_mlx == NULL || fd < 0)
	{
		write(2, "Error\nBruh...\n", ft_strlen("Error\nBruh...\n"));
		return (-1);	
	}
	if (init_my_mlx(my_mlx, fd) == -1)
		freemachine(my_mlx);
	newframe(my_mlx);
	mlx_hook(my_mlx->win_ptr, RED_BUTTON_CODE, DESTROY_EVENT, &freemachine, my_mlx);
	mlx_hook(my_mlx->win_ptr, MOUSE_PRESS_CODE, MOUSE_PRESS_HOOK, &mouseinput, my_mlx);
	mlx_key_hook(my_mlx->win_ptr, &keyinput, my_mlx);
	mlx_loop(my_mlx->win_ptr);
	return (0);
}
