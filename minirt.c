/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 16:21:19 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/07 21:34:03 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	put_pixel(t_data *my_mlx, int x, int y, unsigned color)
{
	int			pos;

	if (x >= 0 && x < my_mlx->scene->width && y >= 0 &&
		y < my_mlx->scene->height)
	{
		pos = y * my_mlx->line_length + x * (my_mlx->bpp / 8);
		if (my_mlx->frame % 2 == 1)
		{
			*(my_mlx->addr + pos + 0) = (char)((color & 0x00FFFFFF) >> 0);
			*(my_mlx->addr + pos + 1) = (char)((color & 0x0000FF00) >> 8);
			*(my_mlx->addr + pos + 2) = (char)((color & 0x00FF0000) >> 16);
		}
		else if (my_mlx->frame % 2 == 0)
		{
			*(my_mlx->addr2 + pos + 0) = (char)((color & 0x00FFFFFF) >> 0);
			*(my_mlx->addr2 + pos + 1) = (char)((color & 0x0000FF00) >> 8);
			*(my_mlx->addr2 + pos + 2) = (char)((color & 0x00FF0000) >> 16);
		}
	}
}

/*
void put_pixel(t_data *my_mlx, int x, int y, unsigned color)
{
    if (x >= 0 && x < data->winx && y >= 0 && y < data->winy)
    {
        int pos = y * data->llen + x * (data->bpp / 8);
        *(unsigned int *)(data->mlx_addr + pos) = color;
    }
}
*/

t_data	*mallocmachine(t_data *my_mlx)
{
	my_mlx = malloc(sizeof(t_data));
	if (my_mlx == NULL)
		return (NULL);
	my_mlx->scene = malloc(sizeof(t_scene));
	if (my_mlx->scene == NULL)
		return (NULL);
	my_mlx->ray = malloc(sizeof(t_ray));
	if (my_mlx->ray == NULL)
		return (NULL);
	my_mlx->ray->length = 0;
	my_mlx->light = NULL;
	my_mlx->cam = NULL;
	my_mlx->sphere = NULL;
	my_mlx->plane = NULL;
	my_mlx->square = NULL;
	my_mlx->cylinder = NULL;
	my_mlx->triangle = NULL;
	my_mlx->frame = 1;
	return (my_mlx);
}

int		newframe(t_data *my_mlx)
{
//	mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img);

//	printf("Destroyed image & ret=%i, clear=%i\n", ret, clear);
//	free(my_mlx->mlx_ptr);
//	free(my_mlx->mlx_img);
//	free(my_mlx->addr);

	mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img2);
	mlx_destroy_image(my_mlx->mlx_ptr, my_mlx->mlx_img);

	my_mlx->mlx_img = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width, my_mlx->scene->height);
	my_mlx->addr = mlx_get_data_addr(my_mlx->mlx_img, &my_mlx->bpp, &my_mlx->line_length, &my_mlx->endian);

	my_mlx->mlx_img2 = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width, my_mlx->scene->height);
	my_mlx->addr2 = mlx_get_data_addr(my_mlx->mlx_img2, &my_mlx->bpp, &my_mlx->line_length, &my_mlx->endian);


	ray(my_mlx);
	if (my_mlx->frame % 2 == 1)
	{
		mlx_clear_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
		mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr, my_mlx->mlx_img, 0, 0);
	}
	else if (my_mlx->frame % 2 == 0)
	{
		mlx_clear_window(my_mlx->mlx_ptr, my_mlx->win_ptr);
		mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr, my_mlx->mlx_img2, 0, 0);
	}
	my_mlx->frame++;
	return (1);
}

int		readinput(int keycode, t_data *my_mlx)
{
	if (keycode == ESCAPE)
	{
		(void)my_mlx;
		free(my_mlx->mlx_img);
		free(my_mlx->mlx_ptr);
		exit(0);
	}
	if (keycode == LEFT_ARROW)
	{
		my_mlx->cam->s[0] = my_mlx->cam->s[0] - 5.0;
		printf("X-5: %f\n", my_mlx->cam->s[0]);
		newframe(my_mlx);
	}
	if (keycode == RIGHT_ARROW)
	{
		my_mlx->cam->s[0] = my_mlx->cam->s[0] + 5.0;
		printf("X-5: %f\n", my_mlx->cam->s[0]);
		newframe(my_mlx);
	}
	if (keycode == UP_ARROW)
	{
		my_mlx->cam->s[1] = my_mlx->cam->s[1] + 5.0;
		printf("Y+5: %f\n", my_mlx->cam->s[1]);
		newframe(my_mlx);
	}
	if (keycode == DOWN_ARROW)
	{
		my_mlx->cam->s[1] = my_mlx->cam->s[1] - 5.0;
		printf("Y-5: %f\n", my_mlx->cam->s[1]);
		newframe(my_mlx);
	}
	if (keycode == NUMONE)
	{
		my_mlx->cam->s[2] = my_mlx->cam->s[2] + 5.0;
		printf("Z+5: %f\n", my_mlx->cam->s[2]);
		newframe(my_mlx);
	}
	if (keycode == NUMZERO)
	{
		my_mlx->cam->s[2] = my_mlx->cam->s[2] - 5.0;
		printf("Z-5: %f\n", my_mlx->cam->s[2]);
		newframe(my_mlx);
	}
	if (keycode == LEFT_CLICK)
	{
		printf("Newframe\n");
		newframe(my_mlx);
	}
	return (1);
}

t_data	*init_my_mlx(int fd)
{
	t_data	*my_mlx;

	my_mlx = NULL;
	my_mlx = mallocmachine(my_mlx);
	if (my_mlx == NULL)
		return (NULL);
	my_mlx->mlx_ptr = mlx_init();
	ft_parser(my_mlx, fd);
	printf("bitch ass\n\n");

	my_mlx->mlx_img2 = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width, my_mlx->scene->height);
	my_mlx->addr2 = mlx_get_data_addr(my_mlx->mlx_img2, &my_mlx->bpp, &my_mlx->line_length, &my_mlx->endian);

	my_mlx->mlx_img = mlx_new_image(my_mlx->mlx_ptr, my_mlx->scene->width, my_mlx->scene->height);
	my_mlx->addr = mlx_get_data_addr(my_mlx->mlx_img, &my_mlx->bpp, &my_mlx->line_length, &my_mlx->endian);
	ray(my_mlx);
	printf("linelength=%i, bpp=%d\n", my_mlx->line_length, my_mlx->bpp);
	my_mlx->win_ptr = mlx_new_window(my_mlx->mlx_ptr, my_mlx->scene->width, my_mlx->scene->height, "Printing RONDJES like a motherfucking boss bitch");

	return (my_mlx);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_data	*my_mlx;

	if (argc != 2 || ft_strnstr(argv[1], ".rt", 20) == 0)
	{
		write(2, "Error\nan explicit error message of your choice\n", 47);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	my_mlx = init_my_mlx(fd);
	mlx_put_image_to_window(my_mlx->mlx_ptr, my_mlx->win_ptr, my_mlx->mlx_img, 0, 0);
//	mlx_key_hook(my_mlx->win_ptr, &readinput, my_mlx);
	mlx_loop(my_mlx->win_ptr);
}
