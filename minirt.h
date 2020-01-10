/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/10 18:57:33 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <math.h>
# include "minilibx_mms_20191025_beta/mlx.h"
# include "includes/libft/libft.h"
# include "includes/gnl/get_next_line.h"
# include "enums.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_sphere
{
	t_vec3			s;
	t_vec3			tmp;
	double			diameter;
	unsigned		colour;
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3			s;
	t_vec3			normal;
	unsigned long	colour;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_square
{
	t_vec3			s;
	t_vec3			v;
	double			size;
	unsigned long	colour;
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	t_vec3				s;
	t_vec3				v;
	double				diameter;
	double				height;
	unsigned			colour;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vec3				s0;
	t_vec3				s1;
	t_vec3				s2;
	t_vec3				normal;
	unsigned			colour;
	struct s_triangle	*next;
}				t_triangle;

typedef struct	s_cam
{
	t_vec3			s;
	t_vec3			v;
	int				fov;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_light
{
	t_vec3			s;
	double			brightness;
	unsigned		colour;
	struct s_light	*next;
}				t_light;

typedef	struct	s_ray
{
	t_vec3			v;
	unsigned		colour;
	double			length;
}				t_ray;

typedef	struct	s_scene
{
	char			*id;
	double			width;
	double			height;
	double			amblight;
	unsigned		amblightcolor;
}				t_scene;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_img;
	void		*mlx_img2;
	void		*win_ptr;
	char		*addr;
	char		*addr2;
	int			frame;
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

/*
**Extra functions
*/
int		ft_amount(long int nb);
int		ft_iswhitespace(char c);
int		ft_objectcheck(const char *id);
double	ft_atof_peer(const char *str, int *i);
int		ft_atoi_peer(const char *str, int *i);
/*
**Vector mathematics
*/
t_vec3	vector_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vector_add(t_vec3 v1, t_vec3 v2);
double	dotproduct(t_vec3 v1, t_vec3 v2);
t_vec3	vec_mult(t_vec3 v1, double d);
double	find_length(t_vec3 s, t_vec3 p);

t_vec3	crossproduct(t_vec3 v1, t_vec3 v2);
/*
**Objects
*/
void				loopspheres(t_data *my_mlx);
int					parse_sphere(t_data *my_mlx, char *line, int *i);
int					parse_square(t_data *my_mlx, char *line, int *i);
int					parse_plane(t_data *my_mlx, char *line, int *i);

unsigned			find_sphere(t_data *my_mlx);
unsigned			find_objects(t_data *my_mlx);
/*
**Rays
*/
t_vec3	normalize_ray(t_vec3 ray);
void	ray(t_data *my_mlx);
/*
**Parsing
*/
unsigned		createhexcolour(char *line, int *i);
void			ft_parser(t_data *my_mlx, int fd);
int				parse_objects(t_data *my_mlx, char *line, int *i);

void			put_pixel(t_data *my_mlx, int x, int y, unsigned color);
int				newframe(t_data *my_mlx);
t_data			*init_my_mlx(int fd);

int				keyinput(int keycode, t_data *my_mlx);
int				mouseinput(int keycode, t_data *my_mlx);
#endif
