/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   click_cylinder_plane.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 21:23:10 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/02/06 21:33:04 by Peer de Bak   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylhelp	click_cylinder_calc(t_cylinder *cyl, t_data *my_mlx, t_vec3 ray)
{
	t_cylhelp	help;

	help.rayorigin = my_mlx->cam->s;
	help.raydir = ray;
	help.cylcenter = cyl->s;
	help.cylrot = cyl->v;
	help.dist = vec3_sub(help.rayorigin, help.cylcenter);
	help.c1 = vec3_sub(help.raydir, vec3_mult(help.cylrot, dotproduct(help.raydir, help.cylrot)));
	help.c2 = vec3_sub(help.dist, vec3_mult(help.cylrot, dotproduct(help.dist, help.cylrot)));
	help.abc0 = vec3_sqr(help.c1);
	help.abc1 = 2.0 * dotproduct(help.c1, help.c2);
	help.abc2 = vec3_sqr(help.c2) - pow((cyl->diameter / 2), 2);
	help.p1 = vec3_sub(help.cylcenter, vec3_mult(help.cylrot, cyl->height / 2.0));
	help.p2 = vec3_add(help.cylcenter, vec3_mult(help.cylrot, cyl->height / 2.0));
	return (help);
}

double	click_cylinder(t_cylinder *cyl, t_data *my_mlx, t_vec3 ray)
{
	t_cylhelp	help;
	t_vec3		q;
	double		res;
	double		dotp1;
	double		dotp2;

	res = -1;
	help = click_cylinder_calc(cyl, my_mlx, ray);
	if (solve_quadratic_equation(&help) == 1)
	{
		q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.y0));
		dotp1 = dotproduct(help.cylrot, vec3_sub(q, help.p1));
		dotp2 = dotproduct(help.cylrot, vec3_sub(q, help.p2));
		if (help.y0 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
			res = help.y0;
		if (help.y1 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
		{
			if (res != -1)
				res = fmin(help.y0, help.y1);
			else
				res = help.y1;
			return (res);
		}
	}
	return (-1);
}

double	click_plane(t_plane *pl, t_data *my_mlx, t_vec3 ray)
{
	t_vec3	sub;
	double	a;
	double	denom;
	double	t;

	sub = vec3_sub(pl->s, my_mlx->cam->s);
	denom = dotproduct(pl->normal, ray);
	if (denom > 0.000001)
	{
		a = dotproduct(sub, pl->normal);
		t = a / denom;
		if (t > 0)
			return (t);
	}
	return (-1);
}