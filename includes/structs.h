/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:15:48 by peer          #+#    #+#                 */
/*   Updated: 2020/04/24 18:15:49 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minirt.h"

typedef struct	s_bmpcol
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_bmpcol;

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

typedef struct	s_quat
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
	struct s_sphere	*next;
	t_vec3			s;
	t_vec3			tmp;
	double			diameter;
	t_col			colour;
}				t_sphere;

typedef struct	s_plane
{
	struct s_plane	*next;
	t_vec3			s;
	t_vec3			normal;
	t_col			colour;
}				t_plane;

typedef struct	s_trihelp
{
	t_vec3			edge0;
	t_vec3			edge1;
	t_vec3			edge2;
	t_vec3			pvec;
	t_vec3			qvec;
	t_vec3			tvec;
	double			u;
	double			v;
	double			det;
	double			invdet;
	double			t;
}				t_trihelp;

typedef struct	s_triangle
{
	struct s_triangle	*next;
	t_vec3				s0;
	t_vec3				s1;
	t_vec3				s2;
	t_vec3				normal;
	t_col				colour;
}				t_triangle;

typedef struct	s_square
{
	struct s_square	*next;
	t_vec3			s;
	t_vec3			normal;
	double			size;
	t_col			colour;
	t_matrix		localmat;
	t_vec3			upvec;
	t_vec3			rightvec;
	t_triangle		tri[2];
}				t_square;

typedef struct	s_cylhelp
{
	t_vec3	rayorigin;
	t_vec3	raydir;
	t_vec3	cylcenter;
	t_vec3	cylrot;
	t_vec3	dist;
	t_vec3	c1;
	t_vec3	c2;
	double	abc0;
	double	abc1;
	double	abc2;
	t_vec3	p1;
	t_vec3	p2;
	double	t0;
	double	t1;
	double	res;
}				t_cylhelp;

typedef struct	s_cylinder
{
	struct s_cylinder	*next;
	t_vec3				s;
	t_vec3				v;
	double				diameter;
	double				height;
	t_col				colour;
}				t_cylinder;

typedef struct	s_cam
{
	struct s_cam	*next;
	t_vec3			s;
	t_vec3			v;
	int				fov;
	t_matrix		c2w;
	t_quat			quat;
}				t_cam;

typedef struct	s_light
{
	struct s_light	*next;
	t_vec3			s;
	double			brightness;
	t_col			colour;
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

typedef struct	s_click
{
	char	identifier;
	char	*object;
	int		index;
	int		state;
	t_vec3	oldray;
	t_vec3	newray;
	double	distance;
	double	dist_r;
	double	dist_up;
	double	dist_fw;
	int		x;
	int		y;
	t_vec3	pos;
	double	sizemult;
	double	heightmult;
	t_vec3	rotation;
	int		mousemovestate;
}				t_click;

typedef struct	s_bonus
{
	void		*uvimg;
	char		*uvaddr;
	int			uvbpp;
	int			uvll;
	int			uvendian;
	int			uvnx;
	int			uvny;
	int			stereoscopy;
	void		*bumpimg;
	char		*bumpaddr;
	int			bumpbpp;
	int			bumpll;
	int			bumpendian;
	int			bumpnx;
	int			bumpny;
}				t_bonus;

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
	int			fd;
	t_scene		*scene;
	t_light		*light;
	t_cam		*cam;
	t_cam		*camhead;
	t_ray		*ray[THREADCOUNT];
	t_sphere	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
	t_click		*click;
	int			bmp;
	t_bonus		*bonus;
}				t_data;

typedef struct	s_arg
{
	t_data		*my_mlx;
	int			threadnr;
}				t_arg;

typedef struct	s_aa
{
	double		pndcx;
	double		pndcy;
	t_col		col1;
	t_col		col2;
	t_col		col3;
	t_col		col4;
}				t_aa;

#endif
