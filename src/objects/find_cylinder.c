/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_cylinder.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer de Bakker <pde-bakk@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:05:36 by pde-bakk       #+#    #+#                */
/*   Updated: 2020/03/07 17:42:19 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylhelp	cylinder_calc(t_cylinder *cyl, t_data *my_mlx, int threadnr)
{
	t_cylhelp	help;

	help.rayorigin = my_mlx->cam->s;
	help.raydir = my_mlx->ray[threadnr]->v;
	help.cylcenter = cyl->s;
	help.cylrot = cyl->v;
	help.dist = vec3_sub(help.rayorigin, help.cylcenter);
	help.c1 = vec3_sub(help.raydir, vec3_mult(help.cylrot,
	dotproduct(help.raydir, help.cylrot)));
	help.c2 = vec3_sub(help.dist, vec3_mult(help.cylrot,
	dotproduct(help.dist, help.cylrot)));
	help.abc0 = vec3_sqr(help.c1);
	help.abc1 = 2.0 * dotproduct(help.c1, help.c2);
	help.abc2 = vec3_sqr(help.c2) - pow((cyl->diameter / 2), 2);
	help.p1 = vec3_sub(help.cylcenter, vec3_mult(help.cylrot,
	cyl->height / 2.0));
	help.p2 = vec3_add(help.cylcenter, vec3_mult(help.cylrot,
	cyl->height / 2.0));
	return (help);
}

int			solve_quadratic_equation(t_cylhelp *help)
{
	double	discriminant;

	discriminant = pow(help->abc1, 2) - 4.0 * help->abc0 * help->abc2;
	if (discriminant < 0.0)
		return (0);
	else if (discriminant < EPSILON)
	{
		help->y0 = -0.5 * help->abc1 / help->abc0;
		help->y1 = help->y0;
	}
	else
	{
		help->y0 = (-help->abc1 + sqrt(discriminant)) / (2.0 * help->abc0);
		help->y1 = (-help->abc1 - sqrt(discriminant)) / (2.0 * help->abc0);
	}
	return (1);
}

void		cylinder_hit(t_ray *ray, t_cylinder *cyl,
			double res, t_cylhelp help)
{
	if (res != -1)
		res = fmin(help.y0, help.y1);
	else
		res = help.y1;
	if (res < ray->length)
	{
		ray->length = res;
		ray->colour = cyl->colour;
		ray->hitnormal = vec3_normalize(vec3_sub(cyl->s,
		vec3_mult(ray->v, res)));
		ray->hitnormal = vec3_mult(ray->hitnormal, -1);
	}
}

int			find_cylinder(t_cylinder *cyl, t_data *my_mlx, int threadnr)
{
	t_cylhelp	help;
	t_vec3		q;
	double		res;
	double		dotp1;
	double		dotp2;

	res = -1;
	help = cylinder_calc(cyl, my_mlx, threadnr);
	if (solve_quadratic_equation(&help) == 1)
	{
		q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.y0));
		dotp1 = dotproduct(help.cylrot, vec3_sub(q, help.p1));
		q = vec3_add(help.rayorigin, vec3_mult(help.raydir, help.y1));
		dotp2 = dotproduct(help.cylrot, vec3_sub(q, help.p2));
		if (help.y0 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
			res = help.y0;
		if (help.y1 > 0.0 && dotp1 > 0.0 && dotp2 < 0.0)
		{
			cylinder_hit(my_mlx->ray[threadnr], cyl, res, help);
		}
		return (res);
	}
	return (0);
}
