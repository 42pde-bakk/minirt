/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 23:07:26 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/05/06 06:26:55 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	*((u_int16_t *)&buf[0x00]) = 0x4d42;
	*((u_int32_t *)&buf[0x02]) = (u_int32_t)size;
	*((u_int32_t *)&buf[0x0A]) = (u_int32_t)0x0E + 40;
	*((u_int32_t *)&buf[0x0E]) = (u_int32_t)40;
	*((u_int32_t *)&buf[0x12]) = (u_int32_t)my_mlx->scene->width;
	*((u_int32_t *)&buf[0x16]) = (u_int32_t)my_mlx->scene->height;
	*((u_int16_t *)&buf[0x1A]) = (u_int16_t)1;
	*((u_int16_t *)&buf[0x1C]) = (u_int32_t)24;
	return (buf);
}

t_col	get_pixel(t_data *my_mlx, int x, int y)
{
	t_col		out;
	unsigned	in;
	int			pos;

	pos = y * my_mlx->line_length + x * my_mlx->bpp / 8;
	in = *(unsigned int*)(my_mlx->addr + pos);
	out = unsigned_to_tcol(in);
	return (out);
}

char	*write_pixels(char *buf, t_data *my_mlx)
{
	u_int32_t	index;
	u_int32_t	x;
	u_int32_t	y;
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

int		bmp(t_data *my_mlx)
{
	char		*buf;
	unsigned	bmpfilesize;

	my_mlx->bmp = open("screenshot.bmp", O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (my_mlx->bmp < 2)
		return (ft_putstr_int("Error\nError opening .bmp file\n", 2));
	bmpfilesize = 14 + 40 + 3 * (int)(my_mlx->scene->width *
			my_mlx->scene->height);
	buf = ft_calloc(bmpfilesize, 1);
	if (!buf)
		return (0);
	buf = write_header(buf, my_mlx);
	buf = write_pixels(buf, my_mlx);
	if (write(my_mlx->bmp, buf, bmpfilesize) < 0)
		ft_putstr_int("Error\nWriting to .bmp file failed\n", 2);
	free(buf);
	if (close(my_mlx->bmp))
		return (ft_putstr_int("Error\nClosing .bmp file failed\n", 2));
	return (0);
}
