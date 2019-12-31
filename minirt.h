/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/12/31 13:36:30 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <math.h>
# include "minilibx_mms_20191025_beta/mlx.h"
# include "includes/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_sphere
{
	float			x;
	float			y;
	float			z;
	float			diameter;
	unsigned long	colour;
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	float			x;
	float			y;
	float			z;
	float			xvector;
	float			yvector;
	float			zvector;
	unsigned long	colour;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_square
{
	float			x;
	float			y;
	float			z;
	float			xvector;
	float			yvector;
	float			zvector;
	float			size;
	unsigned long	colour;
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	float				x;
	float				y;
	float				z;
	float				xvector;
	float				yvector;
	float				zvector;
	float				diameter;
	float				height;
	unsigned long		colour;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	float				x1;
	float				y1;
	float				z1;
	float				x2;
	float				y2;
	float				z2;
	float				x3;
	float				y3;
	float				z3;
	unsigned long		colour;
	struct s_triangle	*next;
}					t_triangle;

typedef struct	s_cam
{
	float			x;
	float			y;
	float			z;
	float			xvector;
	float			yvector;
	float			zvector;
	int	 			fov;
	double			height;
	double			canvx1;
	double			canvx2;
	double			canvy1;
	double			canvy2;
	double			canvZ;
//	double			canvtoprightx;
//	double			canvtoprighty;
//	double			canvtoprightz;
//	double			canvbottomleftx;
//	double			canvbottomlefty;
//	double			canvbottomleftz;
//	double			canvbottomrightx;
//	double			canvbottomrighty;
//	double			canvbottomrightz;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_light
{
	float			x;
	float			y;
	float			z;
	float			brightness;
	unsigned long	colour;
	struct s_light	*next;
}				t_light;

typedef	struct	s_ray
{
	double			x;
	double			y;
	double			z;
	unsigned long	colour;
}				t_ray;

typedef	struct	s_scene
{
	char			*id;//This one is malloc'd through ft_substr
	double			width;
	double			height;
	float			amblight;
	unsigned		amblightcolor;
}				t_scene;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_img;
	void		*win_ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_scene		*scene;
	t_light		*light;
	t_cam		*cam;
	t_ray		*ray;
	t_sphere	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
}				t_data;

int		ft_amount(long int nb);
int		ft_iswhitespace(char c);
int		ft_objectcheck(const char *id);
float	ft_atof_peer(const char *str, int *i);
int		ft_atoi_peer(const char *str, int *i);
void	put_square(t_data *my_mlx, int x, int y, int size, int color);

void	ray(t_data *my_mlx, double canvasx, double canvasy, double canvasz);

unsigned long	createhexcolour(char *line, int *i);
void	ft_parser(t_data *my_mlx, int fd);

int		parse_objects(t_data *my_mlx, char *line, int *i);

void	put_pixel(t_data *my_mlx, int x, int y, int color);
t_data	*init_my_mlx(int fd);

#endif
