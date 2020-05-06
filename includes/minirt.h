/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/24 18:16:13 by peer          #+#    #+#                 */
/*   Updated: 2020/05/06 06:25:08 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "enums.h"
# include "structs.h"
# include "mathematics.h"
# include "parsing.h"
# include "objects.h"
# include "interaction.h"
# include "lighting.h"
# include <stdio.h> //remove pls

# ifndef ALBEDO
#  define ALBEDO 1000.0
# endif
# define EPSILON 1e-6
# define EPSI 1e-6
# define CAM_SPEED 0.5
# define CAM_ROT_SPEED 5.0
# define CAM_FOV_STEP 2.0
# define ROT_DEGREES 90.0
# define MOVE_SPEED -5.0
# define WHITE 0xFFFFFF
# ifndef BONUS
#  define BONUS 0
# endif
# ifndef THREADCOUNT
#  define THREADCOUNT 1
# endif
# ifndef UV
#  define UV -1
# endif
# ifndef SEPIA
#  define SEPIA 0
# endif
# ifndef MOUSEROTATE
#  define MOUSEROTATE 0
# endif
# ifndef STEREOSCOPY
#  define STEREOSCOPY 0
# endif
# ifndef ANTIALIASING
#  define ANTIALIASING 0
# endif
# ifndef RAINBOW
#  define RAINBOW 0
# endif
# ifndef WAVE
#  define WAVE 0
# endif
# ifndef BUMP
#  define BUMP 0
# endif
# ifndef LINUX
#  define LINUX 0
# endif

/*
**../src/extra.c:
*/
int		ft_amount(long int nb);
void	fswap(double *a, double *b);
char	*ft_itoa_base(long long nb, long long base);
int		ft_iswhitespace(char c);
double	ft_atof_peer(const char *str, int *i);
int		ft_atoi_peer(const char *str, int *i);
int		ft_putstr_int(char *s, int fd);

/*
**And scene:
*/

int		newframe(t_data *my_mlx);
int		init_my_mlx(t_data *my_mlx, int fd);
int		freemachine(t_data *my_mlx);
int		exit_putstr(t_data *my_mlx, char *s, int fd);
int		bmp(t_data *my_mlx);
void	get_uvimg(t_data *my_mlx);

void	put_rgb(t_data *my_mlx, int x, int y, t_col rgb);
double	ndcx(t_data *my_mlx, double x);
double	ndcy(t_data *my_mlx, double y);
void	ray(t_data *my_mlx);
void	hit(t_data *my_mlx, int x, int y, int threadnr);
void	*render_pixel(void *param);

#endif
