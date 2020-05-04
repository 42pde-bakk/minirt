/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_pixel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 16:27:07 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/05/04 22:38:41 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	aa_finish(t_arg *arg, int x, int y, t_aa aa)
{
	t_col	out;

	out = colour_add(aa.col1, aa.col2);
	out = colour_add(out, aa.col3);
	out = colour_add(out, aa.col4);
	out = colour_div(out, 4);
	put_rgb(arg->my_mlx, x, y, out);
}

t_col	aa_getcolour(t_arg *arg, double x, double y)
{
	arg->my_mlx->ray[arg->threadnr]->length = __INT_MAX__;
	arg->my_mlx->ray[arg->threadnr]->hitnormal = vec3_new(0.0, 0.0, 0.0);
	arg->my_mlx->ray[arg->threadnr]->colour = colour_new(0.0, 0.0, 0.0);
	arg->my_mlx->ray[arg->threadnr]->v = setcamera(arg->my_mlx,
		ndcx(arg->my_mlx, x), ndcy(arg->my_mlx, y));
	find_objects(arg->my_mlx, arg->threadnr);
	if (arg->my_mlx->ray[arg->threadnr]->length < __INT_MAX__)
		arg->my_mlx->ray[arg->threadnr]->colour =
			light_tracing(arg->my_mlx, arg->threadnr);
	return (arg->my_mlx->ray[arg->threadnr]->colour);
}

#if BONUS == 1 && ANTIALIASING == 1

void	*render_pixel(void *param)
{
	int		x;
	int		y;
	t_arg	*arg;
	t_aa	aa;

	arg = param;
	y = arg->threadnr;
	while (y < arg->my_mlx->scene->height)
	{
		x = 0;
		aa.pndcy = ndcy(arg->my_mlx, y);
		while (x < arg->my_mlx->scene->width)
		{
			aa.col1 = aa_getcolour(arg, x, y);
			aa.col2 = aa_getcolour(arg, (double)x + 0.5, y);
			aa.col3 = aa_getcolour(arg, x, (double)y + 0.5);
			aa.col4 = aa_getcolour(arg, (double)x + 0.5, (double)y + 0.5);
			aa_finish(arg, x, y, aa);
			x++;
		}
		y += THREADCOUNT;
	}
	return (NULL);
}

#else

void	*render_pixel(void *param)
{
	int		x;
	int		y;
	double	pndcy;
	double	pndcx;
	t_arg	*arg;

	arg = param;
	y = arg->threadnr;
	while (y < arg->my_mlx->scene->height)
	{
		x = 0;
		pndcy = ndcy(arg->my_mlx, y);
		while (x < arg->my_mlx->scene->width)
		{
			pndcx = ndcx(arg->my_mlx, x);
			arg->my_mlx->ray[arg->threadnr]->v =
				setcamera(arg->my_mlx, pndcx, pndcy);
			find_objects(arg->my_mlx, arg->threadnr);
			hit(arg->my_mlx, x, y, arg->threadnr);
			x++;
		}
		y = y + THREADCOUNT;
	}
	return (NULL);
}

#endif
