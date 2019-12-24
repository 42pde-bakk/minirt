/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/24 14:13:22 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include "minilibx_mms_20191025_beta/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_img;
	void	*win_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

typedef	struct	s_scene
{
	char	*identifier;
	int		width;
	int		height;
	int		x1;
	int		y1;
	int		z1;
	int		color;
	int		size;
}				t_scene;

void	put_square(t_data *my_mlx, int x, int y, int size, int color);

void	put_pixel(t_data *my_mlx, int x, int y, int color);
t_data	*init_my_mlx(void);

#endif
