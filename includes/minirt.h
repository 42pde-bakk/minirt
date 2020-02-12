/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 18:25:22 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/12 18:39:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "enums.h"
# include "structs.h"
# include "mathematics.h"
# include "parsing.h"
# include "objects.h"
# include "interaction.h"

# ifndef ALBEDO
#  define ALBEDO 40.0
# endif
# define EPSILON 1e-6
# ifndef MAX_RESX
#  define MAX_RESX 420
# endif
# ifndef MAX_RESY
#  define MAX_RESY 420
# endif
# define CAM_SPEED 0.5
# define CAM_ROT_SPEED -5.0
# define CAM_FOV_STEP 2.0
# define ROT_DEGREES 90.0
# define MOVE_SPEED -5.0
# define WHITE 0xFFFFFF

# ifndef UV
#  define UV 0
# endif

/*
**../src/extra.c:
*/
int		ft_amount(long int nb);
char	*ft_itoa_base(long long nb, long long base);
int		ft_iswhitespace(char c);
double	ft_atof_peer(const char *str, int *i);
int		ft_atoi_peer(const char *str, int *i);

/*
**../src/lighting:
*/
t_col	light_tracing(t_data *my_mlx);

int		find_obstacles(t_data *my_mlx, t_vec3 ldir, t_vec3 hitpos);

/*
**And scene:
*/

int		newframe(t_data *my_mlx);
int		init_my_mlx(t_data *my_mlx, int fd);
int 	freemachine(t_data *my_mlx);

double	ndcx(t_data *my_mlx, double x);
double	ndcy(t_data *my_mlx, double y);
void	ray(t_data *my_mlx);

#endif
