/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/11 23:51:58 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		data_initvalues(t_data *my_mlx)
{
	int i;

	i = 0;
	while (i < THREADCOUNT)
	{
		my_mlx->ray[i] = malloc(sizeof(t_ray));
		if (!my_mlx->ray[i])
			return (-1);
		my_mlx->ray[i]->length = __INT_MAX__;
		i++;
	}
	my_mlx->scene->width = -1;
	return (1);
}

int		init_my_mlx(t_data *my_mlx, int fd)
{
	my_mlx->mlx_ptr = mlx_init();
	if (my_mlx->mlx_ptr == NULL)
		return (-1);
	my_mlx->scene = malloc(sizeof(t_scene));
	if (my_mlx->scene == NULL)
		return (-1);
	my_mlx->click = malloc(sizeof(t_click));
	if (my_mlx->click == NULL)
		return (-1);
	if (data_initvalues(my_mlx) == -1)
		return (-1);
	if (ft_parser(my_mlx, fd) == -1 || my_mlx->scene->width < 0)
		return (-1);
	get_uvimg(my_mlx);
	my_mlx->win_ptr = mlx_new_window(my_mlx->mlx_ptr, my_mlx->scene->width,
	my_mlx->scene->height, "MiniPeeRT");
	my_mlx->mlx_img = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width,
		my_mlx->scene->height);
	my_mlx->addr = mlx_get_data_addr(my_mlx->mlx_img, &my_mlx->bpp,
				&my_mlx->line_length, &my_mlx->endian);
	my_mlx->mlx_img2 = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width,
		my_mlx->scene->height);
	my_mlx->addr2 = mlx_get_data_addr(my_mlx->mlx_img2, &my_mlx->bpp,
				&my_mlx->line_length, &my_mlx->endian);
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
			if (ft_strncmp(argv[2], "--save", 6) != 0)
				return (-1);
		}
	}
	return (ret);
}

void	hooks(t_data *my_mlx)
{
	mlx_hook(my_mlx->win_ptr, RED_BUTTON_CODE, DESTROY_EVENT,
			&freemachine, my_mlx);
	mlx_hook(my_mlx->win_ptr, MOUSE_PRESS_CODE, MOUSE_PRESS_HOOK,
			&mouseinput, my_mlx);
	mlx_key_hook(my_mlx->win_ptr, &keyinput, my_mlx);
	mlx_loop(my_mlx->mlx_ptr);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_data	*my_mlx;
	int		argcheckret;

	argcheckret = argcheck(argc, argv);
	if (argcheckret == -1)
		return (ft_putstr_int("Error\nBruh... Check your arguments\n", 2));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_int("Error\nBruh... Wrong file\n", 2));
	my_mlx = ft_calloc(1, sizeof(t_data));
	if (my_mlx == NULL)
		return (ft_putstr_int("Error\nFree bwilbers\n", 2));
	my_mlx->fd = fd;
	if (argcheckret == 2)
		my_mlx->bmp = 1;
	if (init_my_mlx(my_mlx, fd) == -1)
	{
		ft_putstr_fd("Error\nBruv init...\n", 2);
		freemachine(my_mlx);
		return (0);
	}
	newframe(my_mlx);
	hooks(my_mlx);
	return (0);
}
