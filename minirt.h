/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/01/23 00:20:31 by pde-bakk      ########   odam.nl         */
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

# ifndef ALBEDO
#  define ALBEDO 2
# endif

# ifndef EPSILON
#  define EPSILON 1e-6
# endif

# ifndef MAX_RESX
#  define MAX_RESX 420
# endif

# ifndef MAX_RESY
#  define MAX_RESY 420
# endif

# define CAM_SPEED 0.5
# define CAM_ROT_SPEED 5.0
# define CAM_FOV_STEP 2.0
# define ROT_DEGREES 90.0
# define TRANSLATE_STEP 1.0

typedef	struct	s_col
{
	double	r;
	double	g;
	double	b;
}				t_col;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_quat
{
	double	w;
	double	x;
	double	y;
	double	z;
}				t_quat;

typedef	struct	s_matrix
{
	t_vec3	r;
	t_vec3	up;
	t_vec3	fw;
	t_vec3	t;
}				t_matrix;

typedef struct	s_sphere
{
	t_vec3			s;
	t_vec3			tmp;
	double			diameter;
	t_col			colour;
	struct s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3			s;
	t_vec3			normal;
	t_col			colour;
	struct s_plane	*next;
}				t_plane;

typedef struct	s_triangle
{
	t_vec3				s0;
	t_vec3				s1;
	t_vec3				s2;
	t_vec3				normal;
	t_col				colour;
	struct s_triangle	*next;
}				t_triangle;

typedef struct	s_square
{
	t_vec3			s;
	t_vec3			normal;
	double			size;
	t_col			colour;
	t_matrix		localmat;
	t_vec3			upvec;
	t_vec3			rightvec;
	t_triangle		tri[2];
	struct s_square	*next;
}				t_square;

typedef struct	s_cylinder
{
	t_vec3				s;
	t_vec3				v;
	double				diameter;
	double				height;
	t_col				colour;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_cam
{
	t_vec3			s;
	t_vec3			v;
	int				fov;
	t_matrix		c2w;
	t_quat			quat;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_light
{
	t_vec3			s;
	double			brightness;
	t_col			colour;
	struct s_light	*next;
}				t_light;

typedef	struct	s_ray
{
	t_vec3			v;
	t_col			colour;
	double			length;
	t_vec3			hitnormal;
}				t_ray;

typedef	struct	s_scene
{
	char			*id;
	double			width;
	double			height;
	double			ambintensity;
	t_col			amblightcolour;
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
	t_cam		*camhead;
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
int					ft_amount(long int nb);
int					ft_iswhitespace(char c);
int					ft_objectcheck(const char *id);
double				ft_atof_peer(const char *str, int *i);
int					ft_atoi_peer(const char *str, int *i);
/*
**Vector mathematics
*/
t_vec3				vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_add(t_vec3 v1, t_vec3 v2);
double				dotproduct(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_mult(t_vec3 v1, double d);
double				find_length(t_vec3 s, t_vec3 p);
t_vec3				vec3_new(double x, double y, double z);
double				vec3_sqr(t_vec3 vec);
t_vec3				vec3_normalize(t_vec3 ray);
t_vec3				crossproduct(t_vec3 v1, t_vec3 v2);
t_vec3				vec3_perpendicular(t_vec3 v1);
/*
**Objects
*/
void				loopspheres(t_data *my_mlx);
int					parse_sphere(t_data *my_mlx, char *line, int *i);
int					parse_square(t_data *my_mlx, char *line, int *i);
int					parse_plane(t_data *my_mlx, char *line, int *i);

int					find_camera(t_data *my_mlx, char *line, int *i);

int					find_sphere(t_data *my_mlx);
int					find_objects(t_data *my_mlx);
/*
**Rays
*/
void				ray(t_data *my_mlx);
/*
**Parsing
*/
// unsigned		createhexcolour(char *line, int *i);
t_col				parse_tcol(char *line, int *i);
void				ft_parser(t_data *my_mlx, int fd);
int					parse_objects(t_data *my_mlx, char *line, int *i);

void				put_pixel(t_data *my_mlx, int x, int y, unsigned color);
int					newframe(t_data *my_mlx);
t_data				*init_my_mlx(int fd);

int					keyinput(int keycode, t_data *my_mlx);
int					mouseinput(int keycode, t_data *my_mlx);
/*
**obstacles.c
*/
int				plane_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir);
int				sphere_obs(t_data *my_mlx, t_vec3 pos, t_vec3 dir, double distance);
int				find_obstacles(t_data *my_mlx, t_vec3 pos, t_vec3 dir, double distance);
/*
**colour.c
*/
t_col			colour_mult(t_col col, double c1, double c2);
t_col			coltimescol(t_col a, t_col b);
t_col			colour_new(void);
t_col			colour_add(t_col v1, t_col v2);
t_col			colour_check(t_col col);
t_col			col_times_lightratio(t_col col, t_col light, double max);
t_col			colour_mul(t_col coloura, t_col colourb, double mul);
/*
**lighting.c
*/
t_col			ambient_lighting(t_data *my_mlx, t_col	colour);
t_col			light_add(t_data *my_mlx, t_vec3 dir, int ret);
t_col			light_tracing(t_data *my_mlx);
/*
matrices.c
*/
void			printvec(t_vec3 v, char *s);
void			printmatrix(t_matrix v);
void			setmatrix(t_data *my_mlx);
void			setcamera(t_data *my_mlx, double pndcx, double pndcy);
t_matrix		rotx(double camrot);
t_matrix		roty(double camrot);
t_matrix		rotz(double camrot);
t_matrix		rotate(t_vec3 angle);
t_matrix		multmatrix(t_matrix a, t_matrix b);
t_matrix		addmatrix(t_matrix a, t_matrix b);
t_vec3			pleurmatrix(t_vec3 v, t_matrix mat);
/*
degrad.c
*/
double			deg2rad(double degrees);
double			rad2deg(double radians);
t_vec3			rad2degvec(t_vec3 v);
t_vec3			deg2radvec(t_vec3 v);
/*
quaternion.c
*/
t_matrix		mat4_lookat(t_vec3 position, t_vec3 target);
t_matrix		mat4_new(t_vec3	right, t_vec3 up, t_vec3 forward, t_vec3 t);
t_matrix		mat4_angles(t_vec3 angles);

void			printquat(t_quat quat, char *str);
t_matrix		quat_to_matrix(t_quat quat);
t_quat			quat_mult(t_quat a, t_quat b);
t_quat			quat_init(double w, double x, double y, double z);
t_quat     		quat_new(double x, double y, double z, double angle);
t_quat   		quat_lookat_peer(t_vec3 position, t_vec3 dirv);
t_quat   		quat_lookat(t_vec3 to, t_vec3 from);
t_matrix   		ft_newrotate(t_data *my_mlx, t_vec3 angle);
#endif