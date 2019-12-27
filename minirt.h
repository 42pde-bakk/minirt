/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/27 18:30:48 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include "minilibx_mms_20191025_beta/mlx.h"
# include "includes/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_object
{
	float	x1;
	float	y1;
	float	z1;
	float	x2;
	float	y2;
	float	z2;
	float	x3;
	float	y3;
	float	z3;
	float	objsize;
	float	objheight;
	int		objcolor;
}				t_object;

typedef	struct	s_scene
{
	char	*id;//This one is malloc'd through ft_substr
	int		width;
	int		height;
	float	amblight;
	int		amblightcolor;
	int		xcam;
	int		ycam;
	int		zcam;
	float	v1cam;
	float	v2cam;
	float	v3cam;
	int		fov;
	float	xlight;
	float	ylight;
	float	zlight;
	float	brightness;
	int		lightcolor;
	t_object	*object;
}				t_scene;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_img;
	void	*win_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	t_scene	*scene;
}				t_data;

int		ft_amount(long int nb);
int		ft_iswhitespace(char c);
int		ft_objectcheck(const char *id);

void	put_square(t_data *my_mlx, int x, int y, int size, int color);

void	ft_parser(t_data *my_mlx, int fd);

void	put_pixel(t_data *my_mlx, int x, int y, int color);
t_data	*init_my_mlx(int fd);

#endif
