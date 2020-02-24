/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 23:07:26 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/24 17:31:45 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bmp_write_colour(int fd, t_bmpcol colour)
{
	write(fd, &colour.b, 1);
	write(fd, &colour.g, 1);
	write(fd, &colour.r, 1);
}

t_bmpcol	get_pixel(t_data *my_mlx, int x, int y)
{
	t_bmpcol	out;
	char	*img;
	int		pos;

	img = my_mlx->mlx_img;
	pos = y * my_mlx->line_length + x * my_mlx->bpp / 8;
	printf("pos=%d\n", pos);
	out.b = (unsigned char)(img + pos + 0);
	out.g = (unsigned char)(img + pos + 1);
	out.r = (unsigned char)(img + pos + 2);
	// printf("get_pixel: %i\n", (unsigned char)img + pos + 0);
	return (out);
}

void	pad_zeroes(int fd, int length)
{
	int				i;
	unsigned char	c;

	c = 0x00;
	i = 0;
	while (i < length)
	{
		write(fd, &c, 1);
		i++;
	}
}

void	write_header(t_data *my_mlx)
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;

	width = (unsigned int)my_mlx->scene->width;
	height = (unsigned int)my_mlx->scene->height;
	size = 4 * width * height;
	write(my_mlx->bmp, "BM\x00\x00\x00\x00\x00\x00\x00\x00", 10);
	write(my_mlx->bmp, "\x36\x00\x00\x00\x28\x00\x00\x00", 8);
	write(my_mlx->bmp, &width, 4);
	write(my_mlx->bmp, &height, 4);
	write(my_mlx->bmp, "\x01\x00\x18\x00\x00\x00\x00\x00", 8);
	write(my_mlx->bmp, &size, 4);
	pad_zeroes(my_mlx->bmp, 16);
}

int	bmp(t_data *my_mlx)
{
	int		x;
	int		y;
	t_bmpcol	colour;

	my_mlx->bmp = open("screenshot.bmp", O_RDWR | O_CREAT | O_EXCL, 0644);
	if (my_mlx->bmp < 2)
		return (0);
	write_header(my_mlx);
	y = my_mlx->scene->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < my_mlx->scene->width)
		{
			colour = get_pixel(my_mlx, x, y);
			printf("colour=[%d, %d, %d]\n", (int)colour.r, (int)colour.g, (int)colour.b);
			bmp_write_colour(my_mlx->bmp, colour);
			x++;
		}
		if (((int)my_mlx->scene->width * 3) % 4 != 0)
		{
			// printf("zeropadding=%d\n", 4 - (((int)my_mlx->scene->width * 3) % 4));
			pad_zeroes(my_mlx->bmp, 4 - (((int)my_mlx->scene->width * 3) % 4));
		}
		y--;
	}
	close(my_mlx->bmp);
	return (0);
}
