/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 23:07:26 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/25 18:43:19 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	bmp_write_colour(int fd, t_bmpcol colour)
{
	write(fd, &colour.b, 1);
	write(fd, &colour.g, 1);
	write(fd, &colour.r, 1);
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

char	*write_header(char *buf, t_data *my_mlx)
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	size;

	width = (unsigned int)my_mlx->scene->width;
	height = (unsigned int)my_mlx->scene->height;
	size = 4 * width * height;
	*((uint16_t *)&buf[0x00]) = 0x4d42;
	*((uint32_t *)&buf[0x02]) = (uint32_t)size;
	*((uint32_t *)&buf[0x0A]) = (uint32_t)0x0E + 40;
	*((uint32_t *)&buf[0x0E]) = (uint32_t)40;
	*((uint32_t *)&buf[0x12]) = (uint32_t)my_mlx->scene->width;
	*((uint32_t *)&buf[0x16]) = (uint32_t)my_mlx->scene->height;
	*((uint16_t *)&buf[0x1A]) = (uint16_t)1;
	*((uint16_t *)&buf[0x1C]) = (uint32_t)24;
	return (buf);
}

t_col	get_pixel(t_data *my_mlx, int x, int y)
{
	t_col		out;
	unsigned	in;
	char		*img;
	int			pos;

	img = my_mlx->addr;
	pos = y * my_mlx->line_length + x * my_mlx->bpp / 8;
	in = *(unsigned int*)(my_mlx->addr + pos);
	out = unsigned_to_tcol(in);
	return (out);
}

char	*write_pixels(char *buf, t_data *my_mlx)
{
	uint32_t	index;
	uint32_t	x;
	uint32_t	y;
	t_col		col;

	index = 0x0E + 40;
	y = my_mlx->scene->height;
	while (y > 0)
	{
		x = 0;
		while (x < my_mlx->scene->width)
		{
			col = get_pixel(my_mlx, x, y);
			buf[index + 0] = col.b;
			buf[index + 1] = col.g;
			buf[index + 2] = col.r;
			index += 3;
			x++;
		}
		y--;
	}
	return (buf);
}

int	bmp(t_data *my_mlx)
{
	char		*buf;
	unsigned	bmpfilesize;

	my_mlx->bmp = open("screenshot.bmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (my_mlx->bmp < 2)
		return (ft_putstr_int("Error opening .bmp file\n", 2));
	bmpfilesize = 14 + 40 + 3 * (int)(my_mlx->scene->width *
			my_mlx->scene->height);
	buf = ft_calloc(bmpfilesize, 1);
	if (!buf)
		return (0);
	buf = write_header(buf, my_mlx);
	buf = write_pixels(buf, my_mlx);
	if (write(my_mlx->bmp, buf, bmpfilesize) < 0)
		ft_putstr_int("Writing to .bmp file failed\n", 2);
	if (close(my_mlx->bmp))
		return (ft_putstr_int("Closing .bmp file failed\n", 2));
	return (0);
}
